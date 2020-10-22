OCIR_URL := phx.ocir.io
TENANCY := ax8lv72xb3nu
REGISTRY := bsidespdx2020
DOCKER_IMAGE := web300

CONTAINER_TAG := ${OCIR_URL}/${TENANCY}/${REGISTRY}/${DOCKER_IMAGE}

target: container push deploy serve

clean: deleteDocker deleteKube

# Docker Configurations

container:
	docker build --no-cache --tag ${CONTAINER_TAG}_server ../src/server/
	docker build --no-cache --tag ${CONTAINER_TAG}_client ../src/client/

push:
	docker push ${CONTAINER_TAG}_server
	docker push ${CONTAINER_TAG}_client

deleteDocker:
	docker image rm ${CONTAINER_TAG}_server
	docker image rm ${CONTAINER_TAG}_client

# Kubernetes

deploy:
	cat deployment/deploy_server.yaml | kubectl create --namespace bsidespdxctf  -f -
	cat deployment/deploy_client.yaml | kubectl create --namespace bsidespdxctf  -f -

serve:
	kubectl create --namespace bsidespdxctf -f deployment/service_server.yaml
	kubectl create --namespace bsidespdxctf -f deployment/service_client.yaml

deleteKube:
	cat deployment/deploy_server.yaml | kubectl delete --namespace bsidespdxctf -f -
	cat deployment/deploy_client.yaml | kubectl delete --namespace bsidespdxctf -f -
	kubectl delete --namespace bsidespdxctf -f deployment/service_server.yaml
	kubectl delete --namespace bsidespdxctf -f deployment/service_client.yaml
	oci dns record domain delete --zone-name-or-id bsidespdxctf.party --domain cavage-enough-for-you.bsidespdxctf.party --force
