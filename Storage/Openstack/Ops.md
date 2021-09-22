
    systemctl disable --now firewalld
    setenforce 0
    sed -i 's/^SELINUX=.*/SELINUX=permissive/g' /etc/selinux/config

    yum -y update
    yum -y install vim wget curl telnet bash-completion
    yum install -y centos-release-openstack-train
    yum update -y
    yum install -y openstack-packstack
    reboot


    openstack --os-auth-url http://192.168.53.188:5000/v3 --os-project-domain-name Default \
    --os-user-domain-name Default --os-project-name admin --os-username admin token issue

    cat << EOF >> admin-openrc
    export export OS_REGION_NAME=RegionOne
    export OS_PROJECT_DOMAIN_NAME=Default
    export OS_USER_DOMAIN_NAME=Default
    export OS_PROJECT_NAME=admin
    export OS_USERNAME=admin
    export OS_PASSWORD=huy123
    export OS_AUTH_URL=http://192.168.53.188:5000/v3
    export OS_IDENTITY_API_VERSION=3
    export OS_IMAGE_API_VERSION=2
    export PS1='[\u@\h \W(admin-openrc-r1)]\$ '
    EOF


    openstack image create "cirros" \
      --file cirros-0.5.1-x86_64-disk.img \
      --disk-format qcow2 --container-format bare \
      --public
