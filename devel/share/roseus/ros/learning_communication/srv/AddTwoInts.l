;; Auto-generated. Do not edit!


(when (boundp 'learning_communication::AddTwoInts)
  (if (not (find-package "LEARNING_COMMUNICATION"))
    (make-package "LEARNING_COMMUNICATION"))
  (shadow 'AddTwoInts (find-package "LEARNING_COMMUNICATION")))
(unless (find-package "LEARNING_COMMUNICATION::ADDTWOINTS")
  (make-package "LEARNING_COMMUNICATION::ADDTWOINTS"))
(unless (find-package "LEARNING_COMMUNICATION::ADDTWOINTSREQUEST")
  (make-package "LEARNING_COMMUNICATION::ADDTWOINTSREQUEST"))
(unless (find-package "LEARNING_COMMUNICATION::ADDTWOINTSRESPONSE")
  (make-package "LEARNING_COMMUNICATION::ADDTWOINTSRESPONSE"))

(in-package "ROS")





(defclass learning_communication::AddTwoIntsRequest
  :super ros::object
  :slots (_a _b _c _d ))

(defmethod learning_communication::AddTwoIntsRequest
  (:init
   (&key
    ((:a __a) 0)
    ((:b __b) 0)
    ((:c __c) (make-array 11 :initial-element 0 :element-type :integer))
    ((:d __d) (make-array 8 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _a (round __a))
   (setq _b (round __b))
   (setq _c __c)
   (setq _d __d)
   self)
  (:a
   (&optional __a)
   (if __a (setq _a __a)) _a)
  (:b
   (&optional __b)
   (if __b (setq _b __b)) _b)
  (:c
   (&optional __c)
   (if __c (setq _c __c)) _c)
  (:d
   (&optional __d)
   (if __d (setq _d __d)) _d)
  (:serialization-length
   ()
   (+
    ;; int64 _a
    8
    ;; int64 _b
    8
    ;; int64[11] _c
    (* 8    11)
    ;; float64[8] _d
    (* 8    8)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _a
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _a (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _a) (= (length (_a . bv)) 2)) ;; bignum
              (write-long (ash (elt (_a . bv) 0) 0) s)
              (write-long (ash (elt (_a . bv) 1) -1) s))
             ((and (class _a) (= (length (_a . bv)) 1)) ;; big1
              (write-long (elt (_a . bv) 0) s)
              (write-long (if (>= _a 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _a s)(write-long (if (>= _a 0) 0 #xffffffff) s)))
     ;; int64 _b
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _b (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _b) (= (length (_b . bv)) 2)) ;; bignum
              (write-long (ash (elt (_b . bv) 0) 0) s)
              (write-long (ash (elt (_b . bv) 1) -1) s))
             ((and (class _b) (= (length (_b . bv)) 1)) ;; big1
              (write-long (elt (_b . bv) 0) s)
              (write-long (if (>= _b 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _b s)(write-long (if (>= _b 0) 0 #xffffffff) s)))
     ;; int64[11] _c
     (dotimes (i 11)
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke (elt _c i) (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class (elt _c i)) (= (length ((elt _c i) . bv)) 2)) ;; bignum
              (write-long (ash (elt ((elt _c i) . bv) 0) 0) s)
              (write-long (ash (elt ((elt _c i) . bv) 1) -1) s))
             ((and (class (elt _c i)) (= (length ((elt _c i) . bv)) 1)) ;; big1
              (write-long (elt ((elt _c i) . bv) 0) s)
              (write-long (if (>= (elt _c i) 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long (elt _c i) s)(write-long (if (>= (elt _c i) 0) 0 #xffffffff) s)))
       )
     ;; float64[8] _d
     (dotimes (i 8)
       (sys::poke (elt _d i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _a
#+(or :alpha :irix6 :x86_64)
      (setf _a (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _a (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _b
#+(or :alpha :irix6 :x86_64)
      (setf _b (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _b (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64[11] _c
   (dotimes (i (length _c))
#+(or :alpha :irix6 :x86_64)
      (setf (elt _c i) (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf (elt _c i) (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
     )
   ;; float64[8] _d
   (dotimes (i (length _d))
     (setf (elt _d i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;;
   self)
  )

(defclass learning_communication::AddTwoIntsResponse
  :super ros::object
  :slots (_sum ))

(defmethod learning_communication::AddTwoIntsResponse
  (:init
   (&key
    ((:sum __sum) 0)
    )
   (send-super :init)
   (setq _sum (round __sum))
   self)
  (:sum
   (&optional __sum)
   (if __sum (setq _sum __sum)) _sum)
  (:serialization-length
   ()
   (+
    ;; int64 _sum
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _sum
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _sum (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _sum) (= (length (_sum . bv)) 2)) ;; bignum
              (write-long (ash (elt (_sum . bv) 0) 0) s)
              (write-long (ash (elt (_sum . bv) 1) -1) s))
             ((and (class _sum) (= (length (_sum . bv)) 1)) ;; big1
              (write-long (elt (_sum . bv) 0) s)
              (write-long (if (>= _sum 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _sum s)(write-long (if (>= _sum 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _sum
#+(or :alpha :irix6 :x86_64)
      (setf _sum (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _sum (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(defclass learning_communication::AddTwoInts
  :super ros::object
  :slots ())

(setf (get learning_communication::AddTwoInts :md5sum-) "7e4d182a4aadad802a874517b27b4a5a")
(setf (get learning_communication::AddTwoInts :datatype-) "learning_communication/AddTwoInts")
(setf (get learning_communication::AddTwoInts :request) learning_communication::AddTwoIntsRequest)
(setf (get learning_communication::AddTwoInts :response) learning_communication::AddTwoIntsResponse)

(defmethod learning_communication::AddTwoIntsRequest
  (:response () (instance learning_communication::AddTwoIntsResponse :init)))

(setf (get learning_communication::AddTwoIntsRequest :md5sum-) "7e4d182a4aadad802a874517b27b4a5a")
(setf (get learning_communication::AddTwoIntsRequest :datatype-) "learning_communication/AddTwoIntsRequest")
(setf (get learning_communication::AddTwoIntsRequest :definition-)
      "int64 a
int64 b
int64[11] c
float64[8] d
---
int64 sum

")

(setf (get learning_communication::AddTwoIntsResponse :md5sum-) "7e4d182a4aadad802a874517b27b4a5a")
(setf (get learning_communication::AddTwoIntsResponse :datatype-) "learning_communication/AddTwoIntsResponse")
(setf (get learning_communication::AddTwoIntsResponse :definition-)
      "int64 a
int64 b
int64[11] c
float64[8] d
---
int64 sum

")



(provide :learning_communication/AddTwoInts "7e4d182a4aadad802a874517b27b4a5a")


