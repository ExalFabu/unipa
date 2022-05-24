# Barbiere
Nel negozio di un barbiere vi è una sala d'attesa con un divano contenente al massimo 5 persone e un'area dove i clienti possono attendere in piedi.
Per motivi di sicurezza, all'interno del negozio possono sostare al massimo N persone contemporaneamente.
Al negozio lavorano tre barbieri, ciascuno con la propria poltrona per il taglio dei capelli.
Se un cliente entra nel negozio quando la sala d’attesa è piena va via senza attendere il proprio turno. Altrimenti, dapprima si accomoda nell'area di attesa, poi si accomoda nel divano e infine attende di essere chiamato da un barbiere.
Il barbiere serve per primo il cliente in attesa da più tempo, gli taglia i capelli, e provvede al pagamento e al rilascio della ricevuta. Poiché vi è soltanto un registro di cassa, i clienti prima di andare via devono aspettare il proprio turno per pagare.
Si implementi la sincronizzazione tra i clienti e i barbieri usando il costrutto Monitor.
Si discuta inoltre se la soluzione proposta può presentare rinvio indefinito e/o deadlock, e se sì, discutere eventuali modifiche per evitarli.