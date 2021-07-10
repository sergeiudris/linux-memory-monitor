(ns linux-memory-monitor.impl
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