
(cl:in-package :asdf)

(defsystem "nlink_parser-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "getSense" :depends-on ("_package_getSense"))
    (:file "_package_getSense" :depends-on ("_package"))
  ))