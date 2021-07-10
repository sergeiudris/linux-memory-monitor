(ns linux-memory-monitor.main
  (:gen-class)
  (:require
   [clojure.core.async :as a :refer [chan go go-loop <! >! <!! >!!  take! put! offer! poll! alt! alts! close! onto-chan!
                                     pub sub unsub mult tap untap mix admix unmix pipe
                                     timeout to-chan  sliding-buffer dropping-buffer
                                     pipeline pipeline-async]]
   [clojure.string]
   [clojure.java.io :as io]

   [cljctools.fs.runtime.core :as fs.runtime.core]
   [cljctools.fs.protocols :as fs.protocols]

   [linux-memory-monitor.spec :as linux-memory-monitor.spec]))

(println "clojure.core.async.pool-size" (System/getProperty "clojure.core.async.pool-size"))
(println "clojure.compiler.direct-linking" (System/getProperty "clojure.compiler.direct-linking"))
(clojure.spec.alpha/check-asserts true)
(do (set! *warn-on-reflection* true) (set! *unchecked-math* true))

(defn -main [& args]
  (println ::-main)
  (<!! (go
         (let [stateA (atom {})
               system-exit| (chan 1)
               root-dir (fs.runtime.core/path-join (System/getProperty "user.dir"))
               data-dir (fs.runtime.core/path-join root-dir "data")]
           (go
             (<! system-exit|)
             (println ::exit|)
             (println ::exiting)
             (System/exit 0))))))

(comment

  (require
   '[cljctools.fs.runtime.core :as fs.runtime.core]
   :reload)

  ;
  )


