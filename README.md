Modelo in Silico da Encefalomielite Autoimune Experimental (EAE)

Este repositório apresenta uma simulação in silico da Encefalomielite Autoimune Experimental (EAE), desenvolvida em C++ para investigar a dinâmica de desmielinização característica da Esclerose Múltipla (EM). O projeto utiliza modelagem matemática para descrever a interação temporal entre as micróglias, citocinas pró-inflamatórias e oligodendrócitos. 

Fundamentação Teórica

O modelo é baseado em um sistema de Equações Diferenciais Ordinárias (EDOs) fundamentado no trabalho de Lombardo et al. (2017), que descreve a quimiotaxia e a ativação celular. Biologicamente, a simulação mimetiza o processo descrito por Da Silva et al. (2020), onde a imunização contra proteínas da mielina — especificamente a MOG (Myelin Oligodendrocyte Glycoprotein) — desencadeia uma cascata inflamatória mediada por células T e micróglias.

Dinâmica Populacional e Variáveis

O código resolve numericamente as interações entre três componentes principais ao longo de um período de 21 dias:
    Densidade de Micróglias ($M$): Células residentes que, ao serem ativadas, iniciam a resposta inflamatória.
    Concentração de Citocinas ($C$): Sinalizadores químicos pró-inflamatórios responsáveis pela propagação do dano.
    Densidade de Oligodendrócitos ($D$): Células produtoras de mielina que sofrem declínio populacional devido à inflamação.

A simulação parte de condições fisiológicas basais, onde a concentração inicial de citocinas é nula e as densidades celulares seguem os padrões de equilíbrio tecidual estabelecidos na literatura ($100$ $cel \cdot mm^{-2}$ para micróglias e $400$ $cel \cdot mm^{-2}$ para oligodendrócitos).

Implementação Técnica

A resolução das EDOs foi implementada em C++, utilizando o Método de Euler para a integração numérica. Esta abordagem permite observar como uma perturbação imunológica localizada se traduz em danos estruturais na bainha de mielina, oferecendo uma ferramenta computacional para o estudo de mecanismos de progressão da doença e possíveis intervenções terapêuticas.
