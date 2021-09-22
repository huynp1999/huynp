
    systemctl disable --now firewalld
    setenforce 0
    sed -i 's/^SELINUX=.*/SELINUX=permissive/g' /etc/selinux/config

    yum -y update
    yum -y install vim wget curl telnet bash-completion
    yum install -y centos-release-openstack-train
    yum update -y
    yum install -y openstack-packstack
    reboot
