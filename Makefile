# http://www.gnu.org/software/make/manual/make.html
# https://gist.github.com/isaacs/62a2d1825d04437c6f08

SHELL := /bin/bash

main:
	clojure -M:main

repl:
	clj -M:repl

depstar-uberjar:
	clojure -X:depstar uberjar \
    :aot true \
    :jar target/find.jar \
    :verbose true \
    :main-class ipfs-shipyard.find.main

lein-uberjar:
	lein with-profiles +prod uberjar 
# java -Dclojure.core.async.pool-size=1 -jar target/find-standalone.jar	

native:
	lein native-image
