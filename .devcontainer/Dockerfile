FROM korosuke613/etrobo-docker:7.2-2

USER root

RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    astyle \
    && apt-get clean && rm -rf /var/cache/apt/archives/* /var/lib/apt/lists/*

USER etrobo
