## Secured Approach for Launch Files ##
An efficient way of logging into an SSH account rather than using passwords exclusively is using a cryptographic key through a public key authentication process. By using this authentication technique:
1. Passwords can be hidden into encrypted keys rather than explicitly typed in readable files.
2. It is easier to log into many accounts without having to memorize many passwords.
3. Connection can only be established from the device where the private key resides instead of logging in using a password from any computer.

In order to have a launch file work with public key mechanism, some system setups need to be performed:

- An SSH key pair is generated at the main Pi unit using the following command:
```
$ssh-keygen
```
The system will respond by:
```
Generating public/private rsa key pair.
Enter file in which to save the key (/Users/yourname/.ssh/id_rsa):
```
It’s recommended to keep the default location to store the key. Pressing Enter will keep the default settings.
```
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
```
The system here asks to choose a password, the password chosen here is the one used for the SSH login which is RandomPassword in our example as used in the old launch file. Now the public and private keys are generated in the selected directory with names id rsa.pub and id rsa respectively.
- Since we use the same password for all unit Pi’s, we will use the same key for all of them. The following command is applied multiple times with different IP addresses that correspond to the different unit Pi’s. For the HBW for example:
```
ssh-copy-id ubuntu@192.168.0.12
```
where ubuntu is the login username for the Pi’s. The system then responds asking for the login password:
```
/usr/bin/ssh-copy-id: INFO: Source of key(s) to be installed:‘‘/
home/ubuntu/.ssh/id_rsa.pub"
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(
s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed - if
you are prompted now it is to install the new keys
ubuntu@192.168.0.12’s password:
```
Now that we entered the correct password (i.e., RandomPassword), the keys are successfully installed in the unit Pi’s and SSH sessions can be established from the main Pi to the unit Pi’s without having to provide the password inside the launch file.
```
Number of key(s) added: 1
Now try logging into the machine, with‘‘ssh ’ubuntu@192.168.0.12’"
and check to make sure that only the key(s) you wanted were added.
```
- However, unlocking the private key used for the connection requires providing the password for each terminal session once. This can be done before running the launch file or by adding the following lines in the .bashrc file:
```shell
ssh-add &>/dev/null || eval ‘ssh-agent‘ &>/dev/null # start ssh-
agent if not started
[ $? -eq 0 ] && { # ssh-agent started
ssh-add # load key
}
```
Now each time a terminal session starts, it will ask for the password to unlock the private key. The launch file at the main Pi is now ready to run the nodes on all the machines without the passwords typed in it, the machine part in the launch file becomes:
```shell
<launch>
<!-- Declaring Machines -->
  <group>
    <machine
      name="main"
      address="192.168.0.10"
      env-loader="/home/ubuntu/catkin_ws/devel/setup.bash"
      default="true"
      user="ubuntu"
    />

    <!-- Include Files -->
      <include file="$(find ft_industry4_raspi)/src/main/
ft_industry4_params.launch" />
  </group>

  <machine
    name="hbw"
    address="192.168.0.12"
    env-loader="/home/ubuntu/env_hbw.sh"
    default="true"
    user="ubuntu"
  />
```
