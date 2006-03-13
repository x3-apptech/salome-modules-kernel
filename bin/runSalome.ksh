#!/bin/ksh

searchFreePort() {
    echo -n "Searching for a free port for naming service: "
    NSPORT=2810
    export NSPORT
    local limit=$NSPORT
    let limit=limit+100
    while [ 1 ]
    do
        aRes=`netstat -ltn | grep -E :${NSPORT}`
        if [ -z "$aRes" ]; then
            echo ${NSPORT} - Ok
	    local myhost=`hostname`
            OMNIORB_CONFIG=${HOME}/.omniORB_${myhost}_${NSPORT}.cfg
            export OMNIORB_CONFIG
	    local initref="NameService=corbaname::"`hostname`":$NSPORT"
	    export NSPORT
	    if [[ `python -c "import CORBA; print CORBA.ORB_ID"` = "omniORB4" ]]; then
                echo "InitRef = $initref" > $OMNIORB_CONFIG
    	    else
	        echo "ORBInitRef $initref" > $OMNIORB_CONFIG
	    fi
            break
        fi
        echo -n "${NSPORT} "
        if [[ $NSPORT -eq $limit ]] ; then
            echo
            echo "Can't find a free port to launch omniNames"
            echo "Try to kill the running servers and then launch SALOME again."
            exit
        fi
        let NSPORT=NSPORT+1
    done
}

searchFreePort

if [[ "$*" = "-nothing" ]]; then
    echo "port:$NSPORT"
elif [ $# -ne 0 ] ; then
    python -i ${KERNEL_ROOT_DIR}/bin/salome/runSalome.py $* 
else
    python ${KERNEL_ROOT_DIR}/bin/salome/runSalome.py
fi

# -----------------------------------------------------------------------------
# examples:
# ---------
#  $: ${KERNEL_ROOT_DIR}/bin/salome/runSalome
#
#     - parameters for launching are taken from $HOME/.salome/salome.launch;
#     - if the config file does not exist, it is created with default values.
#
#  
#  $: ${KERNEL_ROOT_DIR}/bin/salome/runSalome --modules=GEOM,SMESH,VISU,SUPERV,MED --embedded=registry,study,moduleCatalog,cppContainer --standalone=pyContainer,supervContainer --xterm --killall
#
#     parameters from command line supersede those from $HOME/.salome/salome.launch
#
# Some CORBA servers can be launched in the SALOME_Session_Server's process
# (embedded = same process) or in a separate process (standalone):
# --> registry,study,moduleCatalog,cppContainer
# Other CORBA servers could only be launched in separate process (standalone):
# --> pyContainer,supervContainer
#
# $: ${KERNEL_ROOT_DIR}/bin/salome/runSalome -h
#    help
# -----------------------------------------------------------------------------
#
# l'option -i permet de garder l'interpreteur python ouvert :
# par defaut, les differents serveurs ouvrent des fen�tres xterm
# (cf. runSalome.py)
# le serveur Logger n'est pas obligatoire (comment� dans runSalome.py)
# 
# -----------------------------------------------------------------------------
# Example on CCRT (without ihm) :
# ${KERNEL_ROOT_DIR}/bin/salome/runSalome.py --terminal --modules=MED,CALCULATOR,COMPONENT --standalone=registry,study,moduleCatalog,cppContainer,pyContainer,supervContainer --killall