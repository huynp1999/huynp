#!/bin/bash
if="ens4"
TC=$(which tc)

echo "iptables nat outside";
iptables -t nat -A POSTROUTING -o ens3 -j MASQUERADE

echo "root";
$TC qdisc add dev $if root handle 1: htb default 10 

echo "limit bandwidth";
$TC class add dev $if parent 1:1 classid 1:1 htb rate 2mbit	
$TC filter add dev $if protocol ip parent 1: prio 1 u32 match ip dst 192.168.0.0/24 flowid 1:1 
