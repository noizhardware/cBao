all:
	sudo ./build.sh

emk:
	sudo nano Makefile

go:
	sudo pm2 start server && sudo systemctl restart nginx && sudo nginx -t

stop:
	sudo pm2 delete server

clean:
	sudo rm server

.PHONY: all emk go stop clean
