FROM golang:1.15-alpine AS builder
RUN apk add git
RUN adduser --disabled-password --gecos '' web300vuln
WORKDIR /src/300

ENV GOPATH=/go
COPY go.mod go.sum ./
RUN go mod download

COPY . .

ENV CGO_ENABLED 0

RUN go build -o /src/300/300 /src/300/*.go


FROM scratch
#ENV SERVERIP cavage-enough-for-you.bsidespdxctf.party
#ENV SERVERIP 192.168.1.118
COPY --from=builder /src/300/300 /300-client








COPY --from=builder /etc/passwd /etc/passwd

USER web300vuln
ENTRYPOINT [ "/300-client"]