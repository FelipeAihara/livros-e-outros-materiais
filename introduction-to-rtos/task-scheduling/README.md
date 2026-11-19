### Visão geral

Esse código muda a taxa com que o LED do ESP pisca de acordo com a entrada na serial. Para isso, duas threads
foram criadas: uma lê a serial enquanto a outra faz o LED piscar

OBS.: eu sei que eu deveria ter colocado um mutex ou outra coisa para proteger o recurso compartilhado (o sleep_delay_ms), mas fiquei com preguiça...