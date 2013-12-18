#!/usr/bin/perl
 # -w

use strict;
use Device::SerialPort;
use Data::Dumper qw( Dumper );
use Time::HiRes  qw( usleep );
use Digest::CRC;
use Sys::Syslog;
use Net::OpenSoundControl::Server;

#my $port_name = '/dev/ttyUSB0';		# read hardware
my $port_name = '/dev/ttyNBE';	# programmer board
my $OSC_PORT = 1234;

openlog($0, "ndelay,pid", "local0");

my $port_obj;

$port_obj = new Device::SerialPort($port_name) || die "Can't open $port_name: $!\n";
$port_obj->baudrate(19200);
$port_obj->databits(8);
$port_obj->stopbits(1);
$port_obj->parity("none");

$port_obj->read_char_time(0);
$port_obj->read_const_time(100);

my $server = Net::OpenSoundControl::Server->new(Port => $OSC_PORT, Name => '10.0.1.87', Handler => \&wait_for_osc) || die "Could not start server: $@\n";
syslog('info', "osc server started, listening on port $OSC_PORT");

$server->readloop();



sub send_command {
	my $cmd;
	my $val = chr(shift);

	# build command
	#	$command = 's' . $_ . "\0" x 5;				# L1 - reboots
	#	$command = 's' . "\0" x 1 . $_ . "\0" x 4;	# L2 - ok
	$cmd = 's' . "\0" x 2 . $val . "\0" x 3;	# L3 - ok
	#	$command = 's' . "\0" x 3 . $_ . "\0" x 2;	# L4 - ok
	#	$command = 's' . "\0" x 4 . $_ . "\0" x 1;	# L5 - ok
	#	$command = 's' . "\0" x 5 . $_;				# L6 - ok

	# calculate checksum
	my $ctx = Digest::CRC->new(width=>16, poly=>0x1021);
	$ctx->add($cmd);
	my $checksum = $ctx->digest;
	# ...encode checksum as base-64
	my $hex_checksum;
	$hex_checksum = sprintf("%02x%02x", $checksum >> 8, $checksum & 0xff);

	# encode command as base-64
	my $encoded_command = '';
	foreach (split(//, $cmd)) {
		$encoded_command .= sprintf("%02x", ord $_);
	}

	# assemble command
	$encoded_command .= $hex_checksum . "\n";
	#warn Dumper $encoded_command;

	#$port_obj->write(".");
	#usleep(10_000);

	warn Dumper $encoded_command;
	my ($c, $s);
	my ($timeout, $chars, $status);
	do {
		# send command
		$port_obj->write($encoded_command);
	#	foreach (split(//, $encoded_command)) {
	#		$port_obj->write($_);
	#		usleep(10_000);
	#	}

		# read status
		$timeout = 1;
		$status = '';
		while ($timeout > 0) {
			($c, $s) = $port_obj->read(255);
			if ($c > 0) {
				$chars += $c;
				$status .= $s;
			}
			else {
				$timeout--;
			}
		}
		if ($timeout == 0) {
			#warn "timed out\n";
		}
		warn Dumper $status;
	#	usleep 2000_000;
	} while (!($status =~ /[\!zg]/m)) ;
}

sub wait_for_osc {
	my $i;
	my ($sender, $message) = @_;
	my $ch = $message->[0];
	my $val = $message->[2];
	send_command($val);
	syslog('info', "setting value: $val");
}


END {
	if (defined($port_obj)) {
		$port_obj->close || warn "close failed";
	}
}

1;
