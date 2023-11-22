import subprocess #pour run des commandes shell
import os #operating system, pour des fonctions comme path
import sys #messages derreur


#fonction pour run des commandes shell, utilise subprocess.Popen pour executer les commandes dans un nouveau processus
#le process.communicate attend que la commande sexecute pour retourner le output et lerreur
def run_command(command, working_dir):
    print(f"Executing command: {command}")

    process = subprocess.Popen(command, shell=True, cwd=working_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()

    #decoder de bytes a strings
    if stdout:
        print(stdout.decode())
    if stderr:
        print(stderr.decode(), file=sys.stderr)

def compile_files(working_dir):
    compiler = 'g++'
    std = '--std=c++11'
    files_to_compile = ['01_digraph.cpp', '02_digraph.cpp', '03_digraph.cpp', '04_digraph.cpp', 
                        '05_digraph.cpp', '06_digraph.cpp', '07_digraph.cpp', '08_digraph.cpp',
                        '01_reduire.cpp', '02_reduire.cpp', '03_reduire.cpp', '04_reduire.cpp']

    for file in files_to_compile:
        executable = file.replace('.cpp', '')
        compile_command = f'{compiler} {std} {file} -o {executable}'
        run_command(compile_command, working_dir)

def run_digraph(working_dir):
    digraph_commands = [
        './01_digraph',
        './02_digraph',
        './03_digraph',
        './04_digraph',
        './05_digraph',
        './06_digraph tutte_graph tutte_dettes-prets_sommet tutte_sg_1 tutte_sg_2',
        './07_digraph regular_graph regular_dettes-prets_sommet regular_sg_1 regular_sg_2',
        './08_digraph dorogovtsev_graph dorogovtsev_dettes-prets_sommet dorogovtsev_sg_1 dorogovtsev_sg_2'
    ]
    for command in digraph_commands:
        run_command(command, working_dir)

def run_reduire(working_dir):
    reduire_commands = [
        './01_reduire',
        './02_reduire',
        './03_reduire complete complete_reduction'
    ]
    for command in reduire_commands:
        run_command(command, working_dir)

def clean(working_dir):
    exec_digraph = [f'./{f.replace(".cpp", "")}' for f in os.listdir(working_dir) if f.endswith('_digraph.cpp')]
    exec_reduire = [f'./{f.replace(".cpp", "")}' for f in os.listdir(working_dir) if f.endswith('_reduire.cpp')]
    
    for exec_file in exec_digraph + exec_reduire:
        os.remove(os.path.join(working_dir, exec_file))

def main():
    working_dir = './'  
    compile_files(working_dir)
    run_digraph(working_dir)
    run_reduire(working_dir)
    clean(working_dir)

if __name__ == '__main__':
    main()