### Getting an Ubuntu 16.04 LTS Vagrant box, details [here](https://app.vagrantup.com/ubuntu/boxes/xenial64)
```
vagrant init ubuntu/xenial64
vagrant up
```
### Creating a swap file, details [here](https://digitizor.com/create-swap-file-ubuntu-linux/)
```
cd /
sudo dd if=/dev/zero of=swapfile bs=1M count=3000 # count is in MB
sudo mkswap swapfile
sudo swapon swapfile
sudo nano etc/fstab # Add this line: /swapfile none swap sw 0 0
cat /proc/meminfo # Confirm the swap file is active
```
### Making your Vagrant box work on NTFS, details [here](https://github.com/hashicorp/vagrant/issues/5020#issuecomment-439563796)
1. Assuming you've already done your vagrant init...
2. Insert the following into your Vagrantfile after the line `Vagrant.configure("2") do [config]` worked for me:
`config.ssh.insert_key = false`
