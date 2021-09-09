
    yum install epel-release -y
    yum install ansible git virtualenv -y

    pip3 install netaddr
    
cấu hình cho OSD, MON, MGR, RGW [firewall](https://access.redhat.com/documentation/en-us/red_hat_ceph_storage/3/html/installation_guide_for_red_hat_enterprise_linux/requirements-for-installing-rhcs#configuring-a-firewall-for-red-hat-ceph-storage-install)

    192.168.1.31 mon1
    192.168.1.32 mon2
    192.168.1.33 mon3

    192.168.1.31 osd1
    192.168.1.32 osd2
    192.168.1.33 osd3

    [admin@host ~]$ mkdir ~/ceph-ansible-keys

    [root@host ~]# mkdir /var/log/ansible
    [root@host ~]# chown admin.admin /var/log/ansible 
    [root@host ~]# chmod 755 /var/log/ansible
    
    ssh-keyscan osd1 osd2 osd3 mon1 mon2 mon3 >> ~/.ssh/known_hosts
    # osd3:22 SSH-2.0-OpenSSH_8.0
    # mon1:22 SSH-2.0-OpenSSH_8.0
    # mon2:22 SSH-2.0-OpenSSH_8.0
    # osd1:22 SSH-2.0-OpenSSH_8.0
    # osd1:22 SSH-2.0-OpenSSH_8.0
    # osd1:22 SSH-2.0-OpenSSH_8.0
    # osd2:22 SSH-2.0-OpenSSH_8.0
    # osd2:22 SSH-2.0-OpenSSH_8.0
    # osd2:22 SSH-2.0-OpenSSH_8.0
    # osd3:22 SSH-2.0-OpenSSH_8.0
    # osd3:22 SSH-2.0-OpenSSH_8.0
    # mon1:22 SSH-2.0-OpenSSH_8.0
    # mon1:22 SSH-2.0-OpenSSH_8.0
    # mon2:22 SSH-2.0-OpenSSH_8.0
    # mon2:22 SSH-2.0-OpenSSH_8.0
    # mon3:22 SSH-2.0-OpenSSH_8.0
    # mon3:22 SSH-2.0-OpenSSH_8.0
    # mon3:22 SSH-2.0-OpenSSH_8.0
    
    (venv) [ansibledeploy@ceph01 share]$ chmod 600 ~/.ssh/config
    (venv) [ansibledeploy@ceph01 share]$ ssh-copy-id ansibledeploy@mon1
    /usr/bin/ssh-copy-id: INFO: Source of key(s) to be installed: "/home/ansibledeploy/.ssh/id_rsa.pub"
    /usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
    /usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
    ansibledeploy@mon1's password:

    Number of key(s) added: 1

    Now try logging into the machine, with:   "ssh 'ansibledeploy@mon1'"
    and check to make sure that only the key(s) you wanted were added.
    
    vi /etc/ansible/hosts
    ...
    [mons]
    mon1
    mon2
    mon3 
    [mgrs]
    mon1
    mon2
    mon3
    [osds]
    osd1
    osd2
    osd3
    
    
    
    # sudo touch /var/log/ansible.log
    # sudo chown ansibledeploy:ansibledeploy /var/log/ansible.log
    # sudo chmod 775 /var/log/ansible.log
    
    
    vi /etc/anisble/ansible.cfg
    action_plugins = /usr/share/ceph-ansible/plugins/actions/


This phase can be restarted by running: roles/ceph-osd/tasks/main.yml
