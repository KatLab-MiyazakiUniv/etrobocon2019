cd src
powershell -ExecutionPolicy RemoteSigned docker run --rm -it -v ${PWD}:/home/hrp2/sdk/workspace/product korosuke613/etrobo-docker make_src