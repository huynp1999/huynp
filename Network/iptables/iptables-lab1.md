# Webserver Forward

      iptables -t nat -A POSTROUTING -o ens4 -j MASQUERADE 

hoặc với IP tĩnh, cố định:
      
      iptables -t nat -A POSTROUTING -o ens4 -j SNAT --to-source 192.168.53.117


      iptables -t nat -A PREROUTING -i ens4 -p tcp -d 192.168.53.117 —dport 80 -j DNAT —to 10.2.2.30:80
      iptables -A FORWARD -p tcp -d 10.2.2.30 —dport 80 -j ACCEPT
      
      
