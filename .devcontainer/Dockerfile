FROM korosuke613/etrobo-docker:7.2-2

USER root

RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    astyle \ 
    vim \   
    && apt-get clean && rm -rf /var/cache/apt/archives/* /var/lib/apt/lists/*

USER etrobo


RUN sh -c "$(wget https://raw.githubusercontent.com/ohmybash/oh-my-bash/master/tools/install.sh -O -)"

