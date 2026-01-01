# 1. Name the Final Module (e.g., fruit_basket.ko)
obj-m += fruit_basket.o

# 2. List the Ingredients
# logical name (fruit_basket) + "-objs"
fruit_basket-objs := main.o logic.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean