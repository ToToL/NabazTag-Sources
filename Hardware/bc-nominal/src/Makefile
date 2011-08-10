PREPROC="../utils/preproc.pl"
PREPROC2="../utils/preproc_remove_extra_protos.pl"
COMPILER_DIR="../../metal"
COMPILER="mtl_comp"

nominal.mtl:
	"${PREPROC}" < "main.mtl" | "${PREPROC2}" > "nominal.mtl"
	cp nominal.mtl ../

nominal_simu.mtl:
	"${PREPROC}" < "main_simu.mtl" | "${PREPROC2}" > "nominal_simu.mtl"
	cp nominal_simu.mtl ../

bootc: nominal.mtl compileur
	"${COMPILER_DIR}/${COMPILER}" -s "nominal.mtl" "bootc"
	cp bootc ../

compileur:
	cd ${COMPILER_DIR} && ${MAKE} ${COMPILER}

clean:
	rm -f nominal.mtl nominal_simu.mtl bootc
	cd ${COMPILER_DIR} && ${MAKE} clean
