import os.path
from os import path
from sys import argv

#addressIn = '~/Desktop/SECAR/data/'
addressIn = '/mnt/analysis/e20019/rootfiles/'
addressOut = '../histFiles/'

if(not path.exists(addressOut)):
    os.mkdir(addressOut)

runlist = []
for i in range(len(argv)):
    if i > 0:
        runlist.append(int(argv[i]))

# print ('Overwrite existing files? (y/n)')
# x = input()
x = 'y'

for i in runlist:
    fileInName = addressIn + 'run0' + str(i) + '-00_10us.root'
    fileOutName = addressOut + 'single_0' + str(i) + '.root'
    print('Input file : ' + fileInName)
    if( (not path.exists(fileOutName)) or x=='y'):
        command = 'root -l -q \"run_secarAnalysis.C(\\"{}\\",\\"{}\\",{})\"'.format(fileInName,fileOutName,i)
        os.system(command)
        print('Created output file : ' + fileOutName + '\n')
    else:
        print('Outfile: ' + fileOutName + ' already exists!' + '\n')
print('Processing finished.')
