Algoritmo "Reservas de Cinema"

Var
 filmes: vetor[1..4] de caractere
 precos: vetor[1..4] de real
 lugares: vetor[1..50] de caractere
 opcao, bilhetes, i, lugarescolhido: inteiro
 total: real
 continuar: inteiro
Inicio
    filmes[1] <- "Demon Slayer"
    filmes[2] <- "Jujustu Kaisen"
    filmes[3] <- "Attack on Titan"
    filmes[4] <- "Fate Stay Night"
    
    precos[1] <- 3000
    precos[2] <- 3500
    precos[3] <- 2000
    precos[4] <- 2500
    
    para i de 1 ate 50 faca
       lugares[i] <-"Livre"
       fimpara
       continuar <- 1
       enquanto continuar = 1 faca
       escreval("==== CINEMA GHOST23 ====")
   para i de 1 ate 4 faca
      escreval(i, "-",filmes[i],"| Preço:", precos[i], "kz")
      fimpara
      
      escreval(" Escolha o fime:")
      leia(opcao)
      
      se (opcao < 1) OU (opcao > 4) entao
      escreval("opcao inválida!")
      senao
           escreval("Quantos bilhetes desejas?:")
           leia(bilhetes)
           total <- bilhetes * precos[opcao]
           escreval("Filme escolhido:", filmes[opcao])
           escreval("Total a pagar: ", total,"AKZ")
      escreval("Escolha o lugar: ")
      leia(lugarEscolhido)
        se (lugares[lugarEscolhido] = "Livre") entao
         lugares[lugarEscolhido] <- "Ocupado"
         escreval(" Lugar reservado com sucesso!")
         escreval("Reserva confirmada! Bom filme")
            senao
          escreval(" Lugar já está ocupado!")
          fimse
            fimse
            escreval("Deseja fazer outra reserva?(1-Sim/ 2-Não)")
            leia(continuar)
            fimenquanto
            escreval ("Obrigado por usar o nosso sistema!")
       Fimalgoritmo


Fimalgoritmo