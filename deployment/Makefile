target: container push deploy serve

clean: deleteDocker deleteKube

# Docker Configurations

container:
	make -C ../pwn/100-basic-bof-1/oci/ container
	make -C ../pwn/200-basic-bof-2/oci/ container
	make -C ../pwn/300-speakers/oci/ container
	make -C ../tor/100-tor/oci/ container
	make -C ../tor/200-tor/oci/ container
	make -C ../tor/300-tor/oci/ container
	make -C ../web/100-heading-the-right-way/oci/ container
	make -C ../web/200-socking-it-to-ya/oci/ container
	make -C ../web/300-cavage-enough-for-you/oci/ container

push:
	make -C ../pwn/100-basic-bof-1/oci/ push
	make -C ../pwn/200-basic-bof-2/oci/ push
	make -C ../pwn/300-speakers/oci/ push
	make -C ../tor/100-tor/oci/ push
	make -C ../tor/200-tor/oci/ push
	make -C ../tor/300-tor/oci/ push
	make -C ../web/100-heading-the-right-way/oci/ push
	make -C ../web/200-socking-it-to-ya/oci/ push
	make -C ../web/300-cavage-enough-for-you/oci/ push

deleteDocker:
	make -C ../pwn/100-basic-bof-1/oci/ deleteDocker
	make -C ../pwn/200-basic-bof-2/oci/ deleteDocker
	make -C ../pwn/300-speakers/oci/ deleteDocker
	make -C ../tor/100-tor/oci/ deleteDocker
	make -C ../tor/200-tor/oci/ deleteDocker
	make -C ../tor/300-tor/oci/ deleteDocker
	make -C ../web/100-heading-the-right-way/oci/ deleteDocker
	make -C ../web/200-socking-it-to-ya/oci/ deleteDocker
	make -C ../web/300-cavage-enough-for-you/oci/ deleteDocker

# Kubernetes

deploy:
	make -C ../pwn/100-basic-bof-1/oci/ deploy
	make -C ../pwn/200-basic-bof-2/oci/ deploy
	make -C ../pwn/300-speakers/oci/ deploy
	make -C ../tor/100-tor/oci/ deploy
	make -C ../tor/200-tor/oci/ deploy
	make -C ../tor/300-tor/oci/ deploy
	make -C ../web/100-heading-the-right-way/oci/ deploy
	make -C ../web/200-socking-it-to-ya/oci/ deploy
	make -C ../web/300-cavage-enough-for-you/oci/ deploy

serve:
	make -C ../pwn/100-basic-bof-1/oci/ serve
	make -C ../pwn/200-basic-bof-2/oci/ serve
	make -C ../pwn/300-speakers/oci/ serve
	make -C ../tor/100-tor/oci/ serve
	make -C ../tor/200-tor/oci/ serve
	make -C ../tor/300-tor/oci/ serve
	make -C ../web/100-heading-the-right-way/oci/ serve
	make -C ../web/200-socking-it-to-ya/oci/ serve
	make -C ../web/300-cavage-enough-for-you/oci/ serve

deleteKube:
	make -C ../pwn/100-basic-bof-1/oci/ deleteKube
	make -C ../pwn/200-basic-bof-2/oci/ deleteKube
	make -C ../pwn/300-speakers/oci/ deleteKube
	make -C ../tor/100-tor/oci/ deleteKube
	make -C ../tor/200-tor/oci/ deleteKube
	make -C ../tor/300-tor/oci/ deleteKube
	make -C ../web/100-heading-the-right-way/oci/ deleteKube
	make -C ../web/200-socking-it-to-ya/oci/ deleteKube
	make -C ../web/300-cavage-enough-for-you/oci/ deleteKube
