# Makefile

# Copyright (C) 2020 Richard Smith <richard@ex-parrot.com>
# All rights reserved.

BOOTSTRAP ?= ../bootstrap

init:
	rm -f bin lib include
	ln -s $(BOOTSTRAP)/bin $(BOOTSTRAP)/lib $(BOOTSTRAP)/include .

