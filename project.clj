(def MAIN 'linux-memory-monitor.main)
#_(prn (clojure-version))
#_(prn *command-line-args*)

(defmacro init-fn
  [main-ns args]
  `(clojure.core/apply ~(symbol (str main-ns "/-main")) '~args))

(defproject program "0.1.0"

  :repositories [["central" {:url "https://repo1.maven.org/maven2/"}]
                 ["clojars" {:url "https://clojars.org/repo/"}]
                 ["conjars" {:url "https://conjars.org/repo"}]
                 ["scijava" {:url "http://maven.scijava.org/content/repositories/public/"}]
                 ["jitpack" {:url "https://jitpack.io"}]
                 ["cloudsmith-jvm-libp2p" {:url "https://dl.cloudsmith.io/public/libp2p/jvm-libp2p/maven/"}]]

  :min-lein-version "2.9.3"

  :plugins [[org.clojure/tools.deps.alpha "0.8.677"]
            [lein-tools-deps "0.4.5" :exclusions [org.clojure/tools.deps.alpha]]
            [io.taylorwood/lein-native-image "0.3.1"]]
  :middleware [lein-tools-deps.plugin/resolve-dependencies-with-deps-edn]

  :lein-tools-deps/config {:config-files [:install :user :project]
                           :aliases [:core :program]}

  :global-vars {*warn-on-reflection* true
                *unchecked-math* true
                #_*assert* #_false}

  :repl-options {:init-ns          ~MAIN
                 :main             ~MAIN
                 :init ~(macroexpand  `(init-fn ~MAIN ~*command-line-args*))
                 :host             "0.0.0.0"
                 :port             7788}
  :profiles {:dev  {:main         ^{:skip-aot false} ~MAIN
                    :aot          nil #_[datastore.serdes]
                    :aliases      {"dev" ["trampoline" "run" "-m" (format "%s/-main" ~MAIN)]}
                    :dependencies []}

             :repl {:plugins [[nrepl/nrepl "0.6.0"]
                              [cider/cider-nrepl "0.24.0"]]}

             :prod ^:leaky {:main ~MAIN
                            :uberjar-name "find-standalone.jar"
                            :jar-name     "find.jar"
                            :uberjar-exclusions []
                            :jvm-opts ["-Dclojure.compiler.direct-linking=true" "-Dclojure.core.async.pool-size=1"]
                            :aot  nil #_[datastore.serdes]}
             :uberjar {:aot :all
                       :jvm-opts ["-Dclojure.compiler.direct-linking=true" "-Dclojure.core.async.pool-size=1"]
                       :native-image {:jvm-opts ["-Dclojure.compiler.direct-linking=true"]}}
             :hidpi-ui-scale {:jvm-opts ["-Dglass.gtk.uiScale=2"]}}

  :native-image {:name "program.native"            ;; name of output image, optional
                ;  :graal-bin "/path/to/graalvm/" ;; path to GraalVM home, optional
                 :opts ["--no-server" ;; pass-thru args to GraalVM native-image, optional
                        ; "--report-unsupported-elements-at-runtime"
                        "--allow-incomplete-classpath"
                        "--initialize-at-build-time"
                        "--enable-url-protocols=http"
                        "--verbose"
                        "--no-fallback"]}

  :main ^{:skip-aot false} ~MAIN
  :jvm-opts ["-Xms768m" "-Xmx11998m" "-Dclojure.compiler.direct-linking=true" "-Dclojure.core.async.pool-size=1"]

  :source-paths []
  :java-source-paths ["target/proto" "../../.gitlibs/libs/github.ipld/java-cid/d6b6a7017b5b90cf761e6ec04ceb3d1b2e3aaae9/src/main/java"]
  :resource-paths [] #_["resources" "config"]
  :auto-clean false)