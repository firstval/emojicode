//
//  CapturingCallableScoper.hpp
//  Emojicode
//
//  Created by Theo Weidmann on 27/12/2016.
//  Copyright © 2016 Theo Weidmann. All rights reserved.
//

#ifndef CapturingCallableScoper_hpp
#define CapturingCallableScoper_hpp

#include "SemanticScoper.hpp"
#include <utility>
#include <vector>

namespace EmojicodeCompiler {

class ExpressionAnalyser;

struct VariableCapture {
    VariableCapture(size_t id, Type type, size_t captureId) : sourceId(id), type(std::move(type)), captureId(captureId) {}
    size_t sourceId;
    Type type;
    /// The ID of the variable copy in the Closure
    size_t captureId;
};

/** A @c CapturingCallableScoper can automatically capture unknown variables from another scope. These two
    scopes must share the same instance scope as capturing from instance scopes is not supported. */
class CapturingSemanticScoper : public SemanticScoper {
public:
    CapturingSemanticScoper(ExpressionAnalyser *analyser, bool makeCapturesConstant);

    void setPathAnalyser(PathAnalyser *pa) { pathAnalyser_ = pa; }

    Scope& pushArgumentsScope(PathAnalyser *analyser, const std::vector<Parameter> &arguments,
                              const SourcePosition &p) override;

    ResolvedVariable getVariable(const std::u32string &name, const SourcePosition &errorPosition) override;
    const std::vector<VariableCapture>& captures() const { return captures_; }
private:
    ExpressionAnalyser *analyser_;
    std::vector<VariableCapture> captures_;
    size_t captureId_;
    PathAnalyser *pathAnalyser_ = nullptr;
    bool constantCaptures_;
};

}  // namespace EmojicodeCompiler

#endif /* CapturingCallableScoper_hpp */
