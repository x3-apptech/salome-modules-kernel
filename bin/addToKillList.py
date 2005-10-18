#!/usr/bin/env python

import os, sys, pickle, string

########## adds to the kill list of SALOME one more process ##########
def addToKillList(command_pid, command):
    command=(command.split(" "))[0]

    my_port = 2809
    try:
      file = open(os.environ["OMNIORB_CONFIG"], "r")
      s = file.read()
      while len(s):
        l = string.split(s, ":")
        if string.split(l[0], " ")[0] == "ORBInitRef" or string.split(l[0], " ")[0] == "InitRef" :
          my_port = int(l[len(l)-1])
          pass
        s = file.read()
        pass
    except:
	pass
    #print "myport = ", my_port

    filedict=os.getenv("HOME")+'/'+os.getenv('USER')+"_"+str(my_port)+'_SALOME_pidict'
    try:
        fpid=open(filedict, 'r')
        process_ids=pickle.load(fpid)
        fpid.close()
    except:
        process_ids=[{}]
        pass
        
    already_in=0
    for process_id in process_ids:
        print process_id
        for pid, cmd in process_id.items():
            #print "see process %s : %s"% (pid, cmd[0])
	    if pid == command_pid:
		already_in=1
        pass

    if already_in == 0:
        try:
	    process_ids.append({command_pid: [command]})
    	    fpid=open(filedict,'w')
            pickle.dump(process_ids, fpid)
	    fpid.close()
        except:
	    print "addToKillList: can not add command %s to the kill list"% filedict
    	    pass
	pass

if __name__ == "__main__":
    print sys.argv
    addToKillList(sys.argv[1], sys.argv[2])