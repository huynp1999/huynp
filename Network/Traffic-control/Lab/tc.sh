#!/bin/bash
if4="ens4"
if5="ens5"
down1="2mbit"
down2="8mbit"
up="2mbit"
TC=$(which tc)

echo "nat";
iptables -t nat -A POSTROUTING -o ens3 -j MASQUERADE

echo "limit download";
$TC qdisc add dev $if4 root tbf rate $down1 latency 25ms burst $down1
$TC qdisc add dev $if5 root tbf rate $down2 latency 25ms burst $down2

echo "ingress";
$TC qdisc add dev $if5 handle ffff: ingress
$TC qdisc add dev $if4 handle ffff: ingress

echo "limit upload";
$TC filter add dev $if4 parent ffff: protocol ip prio 1 u32 match ip src 192.168.1.0/24 police rate $up burst $up flowid :1
$TC filter add dev $if5 parent ffff: protocol ip prio 1 u32 match ip src 192.168.2.0/24 police rate $up burst $up flowid :2

