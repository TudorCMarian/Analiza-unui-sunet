# Analiza-unui-sunet
**UNIVERSITATEA TEHNICĂ “GH ASACHI” IAŞI  ![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.001.png)FACULTATEA DE AUTOMATICĂ ŞI CALCULATOARE**  

**SPECIALIZAREA: CALCULATOARE ŞI TEHNOLOGIA INFORMAŢIEI** 

**ACHIZIȚIA ȘI PRELUCRAREA DATELOR - PROIECT** 

**Analiza unui sunet în domeniul timp și**  

**în domeniul frecvență** 

**Student,** 

**Marian Tudor-Constantin Grupa 1310B** 

**Coordonator,** 

**Prof. Ungureanu Florina** 

**Iași, 2024** 

- **Descrierea proiectului** 

`  `Proiectul presupune analiza și prelucrarea datelor dintr-un semnal audio în domeniul timp și în domeniul frecvență.  

`       `Analiza în domeniul timp constă în calcularea valorilor de minim, maxim, indexul acestora, dispersia,  media,  mediana,  numărul  de  treceri  prin  zero  (zero-crossing),  dar  și  realizarea histogramei semnalului. Aceasta mai presupune și filtarea semnalului prin mediere (pe 16 sau 32 de elemente) sau filtrare cu filtru de ordin I, cu alpha în intervalul (0,1), precum și aplicarea anvelopei semnalului pe un grafic deja utilizat, pentru o vizualizare mai în detaliu și în perspectivă. De asemenea, derivata va fi afișată pe un alt grafic. 

`      `Analiza  în  domeniul  frecvență  constă  în  aplicarea  a  două  tipuri  de  ferestre  (Hanning  și Hamming) și a două tipuri de filtre (Eliptic și Chebyshev II, trece sus cu frecvența de tăiere de 800 Hz). În urma aplicării se poate vizualiza și spectrul semnalului, atât nefiltrat, cât și filtrat. 

- **Cerințele proiectului** 

**Etapa I** 

Pentru Etapa I a proiectului s-a utilizat un script în Python cu ajutorul căruia s-a făcut reprezentarea grafică a fișierului audio .wav. Fișierul conține sunetul/semnalul care va fi prelucrat și asupra căruia se va face analiza în domeniul timp și în domeniul frecvență.  

`         `Se realizează reprezentarea pe grafice a semnalului, dar și a histogramei. Se calculează valorile de minim, maxim, indexul acestora, dispersia, media, mediana, numărul de treceri prin zero(zero-crossing) și se afișează pe interfață. Pe un alt grafic se va afișa semnalul filtrat în domeniul timp, fie prin filtrare prin mediere, fie prin filtrare cu element de ordin I. Se va reprezenta anvelopa semnalului, dar și derivata acestuia. 

`        `Graficele obținute în urma analizei se salvează ca imagini jpg. 

**Etapa II** 

În etapa II a proiectului se va face switch către un nou panou inclus în aplicație. Noul panou va fi pentru reprezentarea în domeniul frecvență a semnalului audio. Se utilizează două tipuri de ferestre (Hanning și Hamming) și două tipuri de filtre (Eliptic și Chebyshev II, trece sus cu frecvența de tăiere de 800 Hz) pentru a realiza analiza spectrală a semnalului.

`        `Reprezentarea semnalului se face atât înainte, cât și după filtrare, iar același principiu se aplică spectrului. 

- **Mediu de dezvoltare** 

În realizarea proiectului a fost folosit mediul de dezvoltare NI LabWindows/CVI 2020 (mediu de programare ANSI C, dezvoltat de National Instruments), dar și Python cu bibliotecile NumPy și SciPy pentru conversia semnalului. 

- **Analiza în domeniul timp** 

Execuția scriptului Python realizează conversia fișierului „54.wav’’ în două fișiere cu extensia .txt.  Fișierele  conțin  informații  referitoare  la  frecvența  de  eșantionare  și  numărul  de valori/eșantioane ale semnalului.  

`         `Se realizează afișarea pe un control de tip Graph a semnalului audio inițial. Se dorește calcularea  și  afișarea  valorilor:  minim,  maxim,  indexul  acestora,  medie,  dispersie,  mediana, numărul de treceri prin zero, precum calcularea și afișarea histogramei. 

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.002.png)

Se implementează funcțiile pentru filtrarea semnalului după două metode: 

- **Cu un element de ordin I** 

conform relației:  filt[i] = (1-alpha) \* filt[i-1]+  alpha \* signal[i] 

*-signal* -este vectorul care contine valorile semnalului audio  *-filt*- sunt valorile filtrate.  

Pentru filtrul de ordin I, valorile parametrului alpha se vor afla în intervalul (0,1). Amplitudinea semnalului este mult mai mică față de cea a semnalului inițial. Cu cât valoarea lui alpha este mai aproape de 0 se observă mai bine rezultatul filtrării, iar dacă parametrul alpha are valori apropiate de 1, semnalul filtrat are o amplitudine apropiată de cea a semnalului inițial.

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.003.png)

*alpha = 0.1* 

- **Mediere (16 sau 32 de elemente)** 

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.004.png)

*16 elemente* 

**Anvelopa semnalului**  

Se afișează anvelopa semnalului pe același grafic unde s-a reprezentant semnalul audio inițial. 

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.005.png)

**Histograma și derivata** 

Histograma semnalui și derivata acestuia se afișează în panouri create separat. 

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.006.png)

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.007.png)

- **Analiza în domeniul frecvență** 

`            `Analiza în domeniul frecvență constă în crearea unui nou panou pe care se va realiza afișarea spectrului semnalului pe un control de tip Graph. Pentru realizarea spectrului se aplică inițial o fereastră cu scopul de a aplatiza forma semnalului la capetele intervalului de eşantioane analizat. În acest fel, fiecare buffer de eşantioane va fi asimilat cu o perioadă a semnalului. Apoi se calculează partea pozitivă a spectrului scalat de putere pentru un semnal eşantionat, se generează FrequencyPeak-frecvenţa pentru spectrul de putere și PowerPeak- valoarea maximă din  spectru  de  putere.  Din  cauza  numărului  mare  de  puncte  pe  care  îl  are  semnalul  inițial reprezentarea spectrului s-a realizat prin împărțirea semnalului pe mai multe ferestre care conțin N puncte (N= 1024 sau 2048 sau 4096), pentru Transformata Fourier. Se vor aplica două tipuri de ferestre  (Hanning  și  Hamming)  și  două  tipuri  de  filtre  (Chebyshev  II  și  Eliptic,  trece  sus  cu frecvența de tăiere de 800 Hz), pentru reprezentarea pe o secundă la alegere din semnalul inițial. 

`             `Vom analiza mai întâi efectul ferestruirii semnalului cu fiecare tip de fereastră pus la dispoziție în interfața grafică. 

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.008.jpeg)

***Transformata Fourier calculată în N = 1024 de puncte*** 

**Fereastra Hanning** 

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.009.jpeg)

Se poate observa că fereastra Hanning aplatizează semnalul la capete și îl bombează la mijloc. 

**Fereastra Hamming** 

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.010.jpeg)

Se poate observa că fereastra Hamming are aproximativ același efect ca Hanning, doar că nu la fel de intens. 

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.011.png)

Reprezentarea spectrului are o dimensiune egală cu jumătate din frecvența de eșantionare a semnalului. 

**Filtru Chebyshev II, trece sus cu frecvența de tăiere fcut = 800** 

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.012.jpeg)

**Filtru Eliptic, trece sus cu frecvența de tăiere fcut = 800** 

![](./readmeAspose.Words.42b07bce-68f3-4049-9ab1-dd07f0df2272.013.jpeg)
