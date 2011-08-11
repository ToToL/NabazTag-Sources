NOMINAL_DIR=src

all:
	cd ${NOMINAL_DIR} && ${MAKE} bootc

nominal.mtl:
	cd ${NOMINAL_DIR} && ${MAKE} $@

nominal_simu.mtl:
	cd ${NOMINAL_DIR} && ${MAKE} $@

bootc:
	cd ${NOMINAL_DIR} && ${MAKE} $@

compileur:
	cd ${NOMINAL_DIR} && ${MAKE} $@

clean:
	rm -f nominal.mtl nominal_simu.mtl bootc
	cd ${NOMINAL_DIR} && ${MAKE} $@
