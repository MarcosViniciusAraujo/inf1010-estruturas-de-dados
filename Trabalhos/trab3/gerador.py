import random
import string

def geraPlacaAleatoria():

    letras = ''.join(random.choices(string.ascii_uppercase, k=3))
    numeros = ''.join(random.choices(string.digits, k=4))

    placa = letras  + numeros

    return placa

def escreveArquivo(nome_arquivo):
    file = open(nome_arquivo, "w")

    for i in range(1000):
        file.write(geraPlacaAleatoria())
        file.write('\n')
    
    file.close()

    return 
    

def main():
    escreveArquivo('placas.txt')
    return 1


if __name__ == "__main__":
    main()