apt install nfs-kernel-server


apt install qemu-kvm libvirt-bin bridge-utils
apt install nfs-common
mount 10.2.2.10:/root/sharefolder /var/lib/libvirt/images

/etc/defaults/libvirtd
libvirtd_opts="-l"
