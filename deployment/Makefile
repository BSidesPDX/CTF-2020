target: container push deploy serve

clean: deleteDocker deleteKube

# Docker Configurations

container:
	make -C ../pwn/100-basic-bof/oci/ container
	make -C ../pwn/200-speakers-1/oci/ container
	make -C ../tor/100-tor/oci/ container
	make -C ../web/100-heading-the-right-way/oci/ container
	make -C ../web/200-socking-it-to-ya/oci/ container

push:
	make -C ../pwn/100-basic-bof/oci/ push
	make -C ../pwn/200-speakers-1/oci/ push
	make -C ../tor/100-tor/oci/ push
	make -C ../web/100-heading-the-right-way/oci/ push
	make -C ../web/200-socking-it-to-ya/oci/ push

deleteDocker:
	make -C ../pwn/100-basic-bof/oci/ deleteDocker
	make -C ../pwn/200-speakers-1/oci/ deleteDocker
	make -C ../tor/100-tor/oci/ deleteDocker
	make -C ../web/100-heading-the-right-way/oci/ deleteDocker
	make -C ../web/200-socking-it-to-ya/oci/ deleteDocker

# Kubernetes

deploy:
	make -C ../pwn/100-basic-bof/oci/ deploy
	make -C ../pwn/200-speakers-1/oci/ deploy
	make -C ../tor/100-tor/oci/ deploy
	make -C ../web/100-heading-the-right-way/oci/ deploy
	make -C ../web/200-socking-it-to-ya/oci/ deploy

serve:
	make -C ../pwn/100-basic-bof/oci/ serve
	make -C ../pwn/200-speakers-1/oci/ serve
	make -C ../tor/100-tor/oci/ serve
	make -C ../web/100-heading-the-right-way/oci/ serve
	make -C ../web/200-socking-it-to-ya/oci/ serve

deleteKube:
	make -C ../pwn/100-basic-bof/oci/ deleteKube
	make -C ../pwn/200-speakers-1/oci/ deleteKube
	make -C ../tor/100-tor/oci/ deleteKube
	make -C ../web/100-heading-the-right-way/oci/ deleteKube
	make -C ../web/200-socking-it-to-ya/oci/ deleteKube
