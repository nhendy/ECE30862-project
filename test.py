import glob
import subprocess
import os



test_folder    = './tests/'
result_folder  = './result/'
diff_folder    = './diffs/'

cmd_files       = sorted(glob.glob(test_folder + '*.txt'))
xml_files       = sorted(glob.glob(test_folder + '*.xml'))
expected_files  = sorted(glob.glob(test_folder + '*.out'))


if not os.path.exists(diff_folder):
    os.mkdir(diff_folder)


if not os.path.exists(result_folder):
    os.mkdir(result_folder)


print("\n\n\n\n{:=^160}".format(' Execution starts '))

for test_num, (test_cmd, test_expected, test_xml) in enumerate(zip(cmd_files, expected_files, xml_files)):
    _, file_noext = os.path.split(test_cmd)

    result_path   = os.path.join(result_folder, file_noext +'.out')
    xml_path      = test_xml
    cmd_path      = test_cmd
    expected_path = test_expected
    diff_path     = diff_folder + file_noext + '.diff'

    run_command = "./runner {} < {} > {}".format(xml_path, cmd_path, result_path)
    test_command   = "diff {} {}  > {}".format(result_path, expected_path, diff_path)



    try:
        print("\n\n\n{:=^160}".format(' Test '+ str(test_num) + ' '))
        print("Running " + run_command)
        subprocess.call([run_command], shell = True, timeout= 5)

        print("Testing output of {} on {}".format(test_cmd, test_xml))
        return_code = subprocess.call([test_command], shell=True, timeout=5)

        if return_code == 0:
            print("{:=^160}".format(' Test '+ str(test_num) + ' FAILED!!'))
            print('diff FAILED for output {} of {}'.format(result_path, test_xml))
            exit(0)


    except subprocess.TimeoutExpired:
        print("Executing command file {} timed out, it took more than 5 secs. Fix that first!".format(test_cmd))
        exit(0)



    





