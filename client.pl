#!/usr/bin/perl -w

use strict;
use Device::SerialPort;
use Data::Dumper qw( Dumper );
use Time::HiRes  qw( usleep );
use Digest::CRC;

my $port_name = '/dev/ttyUSB0';		# read hardware
#my $port_name = '/dev/ttyUSB1';	# programmer board
my $port_obj;
my $command;

$port_obj = new Device::SerialPort($port_name) || die "Can't open $port_name: $!\n";
$port_obj->baudrate(19200);
$port_obj->databits(8);
$port_obj->stopbits(1);
$port_obj->parity("none");

$port_obj->read_char_time(0);
$port_obj->read_const_time(100);

$_ = chr($ARGV[0]);

# build command
if (@ARGV) {
	$command = 's' . $_ x 6;
}
else {
	$command = 'z' . '0' x 6;
}

# calculate checksum
my $ctx = Digest::CRC->new(width=>16, poly=>0x1021);
$ctx->add($command);
my $checksum = $ctx->digest;
# ...encode checksum as base-64
my $hex_checksum;
$hex_checksum = sprintf("%02x%02x", $checksum >> 8, $checksum & 0xff);

# encode command as base-64
my $encoded_command = '';
foreach (split(//, $command)) {
	$encoded_command .= sprintf("%02x", ord $_);
}

# assemble command
$encoded_command .= $hex_checksum . "\n";
#warn Dumper $encoded_command;

#$port_obj->write(".");
#usleep(10_000);

my ($c, $s);
my ($timeout, $chars, $status);
do {
	# send command
	$port_obj->write($encoded_command);

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
	usleep 2000_000;
} while (!($status =~ /\!/m)) ;

END {
	if (defined($port_obj)) {
		$port_obj->close || warn "close failed";
	}
}

1;
