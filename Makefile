all:
	@echo "Possiblites :"
	@echo "  make nominal.mtl : génère le nominal.mtl"
	@echo "  make nominal_simu.mtl : génère le nominal.mtl adapté à la simulation"
	@echo "  make bootc : génère le bootcode"
	@echo "  make compilateur : génère le compilateur"
	@echo "  make simulateur : génère le simulateur"
	@echo "  make config_simu : génère le dossier Simu_Work et son contenu"
	@echo "  make clean : Tout nettoyer"

nominal.mtl:
	cd src/bc-nominal && ${MAKE} $@
	cp src/bc-nominal/nominal.mtl nominal.mtl

nominal_simu.mtl:
	cd src/bc-nominal && ${MAKE} $@
	cp src/bc-nominal/nominal_simu.mtl nominal_simu.mtl

bootc:
	cd src/bc-nominal && ${MAKE} $@
	cp src/bc-nominal/bootc bootc

compilateur:
	cd src/metal && ${MAKE} mtl_comp
	cp src/metal/mtl_comp compilateur

simulateur:
	cd src/metal && ${MAKE} mtl_simu
	cp src/metal/mtl_simu simulateur

config_simu: nominal_simu.mtl
	rm -rf Simu_Work
	mkdir Simu_Work
	cp configuration_simu.txt Simu_Work/config_simu.txt
	cp src/metal/conf.bin Simu_Work/conf.bin
	cp nominal_simu.mtl Simu_Work/nominal_simu.mtl
	rm -f nominal_simu.mtl
	sed 's/XmppTcpOpen ip 5222 xSession/XmppTcpOpen ip $(shell grep ^XMPPPORT configuration_simu.txt | cut -d ' ' -f 2) xSession/g' Simu_Work/nominal_simu.mtl > Simu_Work/nominal_simu.mtl2
	mv Simu_Work/nominal_simu.mtl2 Simu_Work/nominal_simu.mtl
	sed 's#\(addnewdns..\)\\192.168.1.1#\1\\$(shell grep ^DNS configuration_simu.txt | cut -d ' ' -f 2 | sed 's/\./\\\\/g')#g' Simu_Work/nominal_simu.mtl > Simu_Work/nominal_simu.mtl2
	mv Simu_Work/nominal_simu.mtl2 Simu_Work/nominal_simu.mtl
	sed 's#\(set netip=.\)\\127.0.0.1#\1\\$(shell grep ^IP configuration_simu.txt | cut -d ' ' -f 2 | sed 's/\./\\\\/g')#g' Simu_Work/nominal_simu.mtl > Simu_Work/nominal_simu.mtl2
	mv Simu_Work/nominal_simu.mtl2 Simu_Work/nominal_simu.mtl
	sed 's/"conf.bin"/"Simu_Work\/conf.bin"/g'  Simu_Work/nominal_simu.mtl > Simu_Work/nominal_simu.mtl2
	mv Simu_Work/nominal_simu.mtl2 Simu_Work/nominal_simu.mtl

clean:
	cd src/bc-nominal && ${MAKE} $@
	cd src/metal && ${MAKE} $@
	rm -rf nominal.mtl nominal_simu.mtl bootc compilateur simulateur Simu_Work
