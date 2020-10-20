target: container push deploy serve

clean: deleteDocker deleteKube

# Docker Configurations

container:
	make -C ../pwn/100-basic-bof/oci/ container
	make -C ../tor/100-tor/oci/ container

push:
	make -C ../pwn/100-basic-bof/oci/ push
	make -C ../tor/100-tor/oci/ push

deleteDocker:
	make -C ../pwn/100-basic-bof/oci/ deleteDocker
	make -C ../tor/100-tor/oci/ deleteDocker

# Kubernetes

deploy:
	make -C ../pwn/100-basic-bof/oci/ deploy
	make -C ../tor/100-tor/oci/ deploy

serve:
	make -C ../pwn/100-basic-bof/oci/ serve
	make -C ../tor/100-tor/oci/ serve

deleteKube:
	make -C ../pwn/100-basic-bof/oci/ deleteKube
	make -C ../tor/100-tor/oci/ deleteKube
