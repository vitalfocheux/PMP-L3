#ifndef SIGNAL_H
#define SIGNAL_H

namespace sig {

  class DiscardCombiner {
  public:
    using result_type = /* implementation defined */;

    template<typename U>
    void combine(/* implementation defined */ item) {
      // implementation defined
    }

    result_type result() {
      // implementation defined
    }
  };

  template<typename T>
  class LastCombiner {
  public:
    using result_type = /* implementation defined */;

    template<typename U>
    void combine(/* implementation defined */ item) {
      // implementation defined
    }

    result_type result() {
      // implementation defined
    }
  };

  template<typename T>
  class VectorCombiner {
  public:
    using result_type = /* implementation defined */;

    template<typename U>
    void combine(/* implementation defined */ item) {
      // implementation defined
    }

    result_type result() {
      // implementation defined
    }
  };

  template<typename Signature, typename Combiner = DiscardCombiner>
  class Signal {
  public:
    using combiner_type = /* implementation defined */;

    using result_type = /* implementation defined */;

    Signal(Combiner combiner = Combiner()) {
      // implementation defined
    }

    std::size_t connectSlot(std::function<Signature> callback) {
      // implementation defined
    }

    void disconnectSlot(std::size_t id) {
      // implementation defined
    }

    result_type emitSignal(Args... args) {
      // implementation defined
    }
  };

}

#endif // SIGNAL_H
