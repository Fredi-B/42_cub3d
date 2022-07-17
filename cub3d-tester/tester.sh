#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'

# VALID MAP CHECK MANDATORY
echo -e "${YELLOW}STARTING VALID MAP CHECK MANDATORY:"
i=0
while [ $i -le 86 ]
do
	./cub3D ./maps/valid_maps/$i.cub &
	timer=0
	while [ $timer -le 20 ]
	do
		echo -e "${YELLOW} MAP $i"
		sleep 1
		if pgrep -x "cub3D" > /dev/null; then
			break
		fi
		timer=$(($timer + 1))
	done
	if [ $timer -ge 20 ]
	then
		echo -e "${RED}Map failed:"
		echo -e "${YELLOW}$i.cub"
		pkill -9 cub3D
		exit 0
	fi;
	pkill -9 cub3D
	i=$(($i + 1))
done

echo -e "${GREEN}All valid maps passed mandatory Part!"

# INVALID MAP CHECK MANDATORY
echo -e "${YELLOW}STARTING INVALID MAP CHECK MANDATORY:"

i=171
while [ $i -le 176 ]
do
	echo -e "${YELLOW} MAP $i"
	../cub3D ./maps/invalid_maps/$i.cub &
	sleep 1
	if pgrep -x "cub3D" > /dev/null;
	then
		echo -e "${RED}Map failed during invalid map check:"
		echo -e "${YELLOW}$i.cub"
		pkill -9 cub3D
		exit 0
	fi;
	pkill -9 cub3D
	i=$(($i + 1))
done

echo -e "${GREEN}All invalid maps passed mandatory part!"

# VALID MAP CHECK BONUS
echo -e "${YELLOW}STARTING VALID MAP CHECK BONUS:"
i=0
while [ $i -le 86 ]
do
	./cub3D_bonus ./maps/valid_maps/$i.cub &
	timer=0
	while [ $timer -le 20 ]
	do
		echo -e "${YELLOW} MAP $i"
		sleep 1
		if pgrep -x "cub3D_bonus" > /dev/null; then
			break
		fi
		timer=$(($timer + 1))
	done
	if [ $timer -ge 20 ]
	then
		echo -e "${RED}Map failed:"
		echo -e "${YELLOW}$i.cub"
		pkill -9 cub3D_bonus
		exit 0
	fi;
	pkill -9 cub3D_bonus
	i=$(($i + 1))
done

echo -e "${GREEN}All valid maps passed bonus part!"

# INVALID MAP CHECK BONUS
echo -e "${YELLOW}STARTING INVALID MAP CHECK BONUS:"

i=0
while [ $i -le 176 ]
do
	echo -e "${YELLOW} MAP $i"
	./cub3D_bonus ./maps/invalid_maps/$i.cub &
	sleep 1
	if pgrep -x "cub3D_bonus" > /dev/null;
	then
		echo -e "${RED}Map failed during invalid map check:"
		echo -e "${YELLOW}$i.cub"
		pkill -9 cub3D_bonus
		exit 0
	fi;
	pkill -9 cub3D_bonus
	i=$(($i + 1))
done

echo -e "${GREEN}All invalid maps passed bonus part!"
