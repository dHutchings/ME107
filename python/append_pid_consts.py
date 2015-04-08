import csv
import sys, getopt
import os

location = os.getcwd()

def const_merge(direct): #takes the directory nessisary. Assumes data.csv already exists.
    constants = open( direct+'/pidConstants.csv','w')
    tom = open(direct+'/tom.csv','r')
    content = tom.readlines()
    indices = [i for i, x in enumerate(content) if x == "Constants are\n"]
    #print indices
    if len(indices) == 2:
        #print indices[1]
        kp = content[indices[1] + 1][5:-2]
        ki = content[indices[1] + 2][5:-2]
        kd = content[indices[1] + 3][5:-2]
        constants.write(kp + ',' + ki + ',' + kd )

def main(argv):

    
    opts, args = getopt.getopt(argv,'')
    """
    time = args[0];
    tom = args[1];
    jerry = args[2];
    output = args[3];


    tom_sant = sanitize_data(to_list(tom))
    jerry_sant = sanitize_data(to_list(jerry))
    time_sant = sanitize_data(to_list(time))

    if ( len(tom_sant) != len(jerry_sant)) or ( len(tom_sant) != len(time_sant)) or ( len(jerry_sant) != len(time_sant)) :

        print('tom= ' + str(len(tom_sant)))
        print('jerry = ' + str(len(jerry_sant)))
        print('time = ' + str(len(time_sant)))
        raise NameError('Wrong Sizes!')


    f = open(output,'w')

    for i in xrange(len(time_sant)):
        f.write( str(time_sant[i]) + ',' + str(tom_sant[i]) + ',' + str(jerry_sant[i]) + '\n' )
    f.close()
    """
    targetDir = args[0]
    print targetDir

    for subdir, dirs, files in os.walk(targetDir):  #looks for all directorys       
        for subdir, dirs, files in os.walk(subdir):  #looks over all files in that sub dir
            if any('data.csv' in file for file in files): #if it contains 'data.csv'
                #print files
                print subdir  #each subdirectory.
                #run the merge code!
                const_merge(subdir)

if __name__ == "__main__":
   main(sys.argv[1:])  #pass in target directory.