NOMINAL_DIR=src

all:
	cd ${NOMINAL_DIR} && ${MAKE} bootc
	cp ${NOMINAL_DIR}/bootc .
	cp ${NOMINAL_DIR}/nominal.mtl .

nominal.mtl:
	cd ${NOMINAL_DIR} && ${MAKE} $@
	cp ${NOMINAL_DIR}/nominal.mtl .

nominal_simu.mtl:
	cd ${NOMINAL_DIR} && ${MAKE} $@
	cp ${NOMINAL_DIR}/nominal_simu.mtl .

bootc:
	cd ${NOMINAL_DIR} && ${MAKE} $@
	cp ${NOMINAL_DIR}/bootc .

clean:
	rm -f nominal.mtl nominal_simu.mtl bootc
	cd ${NOMINAL_DIR} && ${MAKE} $@
