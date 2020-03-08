import os
from glob import glob

dir_path = os.path.dirname(os.path.realpath(__file__))
allTestInclude_gen_path = dir_path + '/allTestInclude.h'
allTestReg_gen_path = dir_path + '/allTestReg.h'

allTestInclude_gen = open(allTestInclude_gen_path,'w')
allTestReg_gen = open(allTestReg_gen_path,'w')
allTestIncludeFiles = glob(dir_path + '/Test*.h')
allTestIncludeFiles = [ include.split('/')[-1].split('.')[0] for include in allTestIncludeFiles]
allTestIncludeFiles = sorted(set(allTestIncludeFiles) - {'Test'})

allTestIncludeString = [ '#include <'+include+'.h>' for include in allTestIncludeFiles]
allTestIncludeString = '\n'.join(allTestIncludeString)
allTestInclude_gen.write(allTestIncludeString)

allTestRegString = ''
for include in allTestIncludeFiles:
	allTestRegString += 'testMenu->RegisterTest<test::'+include+'>("'+include+'");\n'

allTestReg_gen.write(allTestRegString)


allTestInclude_gen.close()
allTestReg_gen.close()