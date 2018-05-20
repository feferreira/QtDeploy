pipeline {
  agent any
  stages {
    stage('qmake') {
      steps {
        sh '''/opt/Qt/5.10.1/gcc_64/bin/qmake
'''
      }
    }
    stage('make') {
      steps {
        sh 'make'
      }
    }
  }
}