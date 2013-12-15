#!/usr/bin/perl -w

use strict;
use Device::SerialPort;
use Data::Dumper qw(Dumper);
use Time::HiRes  qw( usleep );
use Digest::CRC;

my $port_name = '/dev/ttyUSB1';
my $port_obj;

$port_obj = new Device::SerialPort($port_name) || die "Can't open $port_name: $!\n";
$port_obj->baudrate(19200);
$port_obj->databits(8);
$port_obj->stopbits(1);
$port_obj->parity("none");

$_ = chr($ARGV[0]);


my $command = 's' . $_ x 6;

my $ctx = Digest::CRC->new(width=>16, poly=>0x1021);
$ctx->add($command);
my $checksum = $ctx->digest;
my $hex_checksum;
$hex_checksum = sprintf("%02x%02x", $checksum >> 8, $checksum & 0xff);

my $encoded_command = '';
foreach (split(//, $command)) {
	$encoded_command .= sprintf("%02x", ord $_);
}

$encoded_command .= $hex_checksum . "\n";
warn Dumper $encoded_command;

foreach (split(//, $encoded_command)) {
$port_obj->write($_);
	usleep(1000);
}
my ($c, $string) = $port_obj->read(1);
print Dumper ($c, $string);

END {
	if (defined($port_obj)) {
		$port_obj->close || warn "close failed";
	}
}

1;
