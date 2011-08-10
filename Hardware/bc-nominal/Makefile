NOMINAL_DIR=nominal_splitted

nominal.mtl:
	cd ${NOMINAL_DIR} && ${MAKE} $@

nominal_simu.mtl:
	cd ${NOMINAL_DIR} && ${MAKE} $@

bootc: nominal.mtl compileur
	cd ${NOMINAL_DIR} && ${MAKE} $@

compileur:
	cd ${NOMINAL_DIR} && ${MAKE} $@

clean:
	rm -f nominal.mtl nominal_simu.mtl bootc
	cd ${NOMINAL_DIR} && ${MAKE} $@
