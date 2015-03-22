import csv
import sys, getopt

def merge_datalogs(tom, jerry, time):
    
    tom_sant = sanitize_data(tom)
    print(tom_sant)
    #read each list item by item.  Try to convert to int.  if it doesn't, advance that one by 1.
#    for i in range(1,len(tom)):
#        if is_num(tom(i)) and is_num(jerry(i)):
#            out_file.append((ratio*tom(i), ratio*jerry(i), time(i))


    #return list_to_csv(out_file)
    return 0

def sanitize_data(lst): #returns only floats!
    out = []
    for s in lst:
        try:
            out.append(float(s))
        except ValueError:
            print('Removing ' + str(s) + ' from list')
    return out



def to_list(filename):
    lines = [line.strip() for line in open(filename)]
    return lines

def main(argv):

    
    r = 1.0

    opts, args = getopt.getopt(argv,'')

    time = args[0];
    tom = args[1];
    jerry = args[2];
    output = args[3];
    #file_out = merge_datalogs(tom, jerry, time, r)


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


if __name__ == "__main__":
   main(sys.argv[1:])