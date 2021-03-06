# SYSTEMD

* [CONFIGURING](CONFIGURING.md)
* [HOW-TO-BUILD](HOW-TO-BUILD.md)

## copy (or replace) fhq-server.service

```
$ sudo cp ../fhq-server/install_files/fhq-server.service  /etc/systemd/system/fhq-server.service
```

## Create directories

```
$ sudo mkdir /var/log/fhq-server
$ sudo mkdir /usr/share/fhq-server
```

## Copy config

```
$ sudo cp ../fhq-server/install_files/fhq-server.conf.example /etc/fhq-server/conf.ini
```

## Reload and restart

```
$ sudo systemctl daemon-reload
$ sudo systemctl enable fhq-server
$ sudo systemctl restart fhq-server.service
```

## Uninstall

```
$ sudo systemctl stop fhq-server.service
$ sudo systemctl disable fhq-server.service
$ sudo rm /etc/systemd/system/fhq-server.service
$ sudo systemctl daemon-reload
$ sudo systemctl reset-failed
```
