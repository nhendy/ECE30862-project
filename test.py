import glob
import subprocess
import os



test_folder    = './tests/'
result_folder  = './result/'
diff_folder    = './diffs/'

cmd_files       = sorted(glob.glob(test_folder + '*.txt'))
xml_files       = sorted(glob.glob(test_folder + '*.xml'))
expected_files  = sorted(glob.glob(test_folder + '*.out'))

print("\n\n\n\n================= Execution Starts =================")

for test_cmd, test_expected, test_xml in zip(cmd_files, expected_files, xml_files):
    _, file_noext = os.path.split(test_cmd)

    result_path   = os.path.abspath(os.path.join(result_folder, file_noext +'.out'))
    xml_path      = os.path.abspath(test_xml)
    cmd_path      = os.path.abspath(test_cmd)
    expected_path = os.path.abspath(test_expected)
    diff_path     = os.path.abspath(diff_folder + file_noext + '.diff')

    run_command = "./runner {} < {} > {}.".format(xml_path, cmd_path, result_path)
    test_command   = "diff {} {}  > {}".format(result_path, expected_path, diff_path)



    try:
        print("Running " + run_command)
        subprocess.call([run_command], shell = True, timeout= 5)

        print("\n\n\nTesting output of {} on {}".format(test_cmd, test_xml))
        return_code = subprocess.call([test_cmd], shell=True, timeout=5)

        if return_code == 0:
            print('diff FAILED for output {} of {}'.format(result_path, test_xml))
            exit(0)


    except TimeoutError:
        print("Executing command file {} timed out, it took more than 5 secs. Fix that first!".format(test_cmd))
        exit(0)



    





