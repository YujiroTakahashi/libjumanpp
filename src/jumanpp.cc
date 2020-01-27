#include "jpp_jumandic_cg.h"
#include "core/analysis/analyzer_impl.h"
#include "jumandic/shared/juman_format.h"
#include "jumandic/shared/jumandic_env.h"
#include "jumandic/shared/jumanpp_args.h"
#include "util/logging.hpp"

#include "jumanpp/jumanpp.h"

struct JumanppContext {
    jumanpp::jumandic::JumanppConf conf;
    jumanpp::core::JumanppEnv env;
    jumanpp_generated::JumandicStatic features;
    jumanpp::core::analysis::Analyzer analyzer;
};

croco::Jumanpp::Jumanpp(std::string modelpath)
{
    jumanpp::util::logging::CurrentLogLevel = static_cast<jumanpp::util::logging::Level>(0);
    JumanppContext *context = new JumanppContext;

    context->conf.modelFile = modelpath;
    context->conf.rnnConfig.nceBias = 5.62844432562;
    context->conf.rnnConfig.unkConstantTerm = -3.4748115191;
    context->conf.rnnConfig.unkLengthPenalty = -2.92994951022;
    context->conf.rnnConfig.perceptronWeight = 1;
    context->conf.rnnConfig.rnnWeight = 0.0176;

    context->env.loadModel(context->conf.modelFile.value());
    context->env.setBeamSize(context->conf.beamSize);
    context->env.setGlobalBeam(context->conf.globalBeam, context->conf.rightCheck, context->conf.rightBeam);
    context->env.setRnnConfig(context->conf.rnnConfig);
    context->env.initFeatures(&context->features);
    context->env.makeAnalyzer(&context->analyzer);

    _handle = static_cast<void*>(context);
}

croco::Jumanpp::~Jumanpp() 
{
    jumanpp::util::logging::CurrentLogLevel = static_cast<jumanpp::util::logging::Level>(0);
    if (nullptr != _handle) {
        delete static_cast<JumanppContext*>(_handle);
    }
}

std::vector<croco::Jumanpp::Node> croco::Jumanpp::analyze(std::string data)
{
    JumanppContext *context = static_cast<JumanppContext*>(_handle);
    context->analyzer.analyze(jumanpp::StringPiece(data));

    jumanpp::jumandic::output::JumandicFields fields;
    jumanpp::core::analysis::AnalysisPath cursor;
    jumanpp::core::analysis::NodeWalker walker;
    jumanpp::jumandic::JumandicIdResolver idResolver;

    auto &om  = context->analyzer.output();
    auto *ptr = context->analyzer.impl()->lattice();

    fields.initialize(om);
    cursor.fillIn(ptr);
    idResolver.initialize(om.dic());


    std::vector<Node> retval;
    while (cursor.nextBoundary()) {
        jumanpp::core::analysis::ConnectionPtr cptr;
        if (!cursor.nextNode(&cptr)) {
            return retval;
        }

        if (!om.locate(cptr.latticeNodePtr(), &walker)) {
            return retval;
        }

        if (!walker.next()) {
            return retval;
        }
        auto fieldBuffer = walker.features();

        jumanpp::jumandic::JumandicPosId rawId{
            fieldBuffer[1], 
            fieldBuffer[2],
            fieldBuffer[4],  // conjForm and conjType are reversed
            fieldBuffer[3]
        };
        auto newId = idResolver.dicToJuman(rawId);

        Node value = {
            fields.surface[walker].str(),
            fields.reading[walker].str(),
            fields.baseform[walker].str(),
            "*", "*", "*", "*", "*", "",
            0, 0, 0, 0, 0
        };

        if (fields.pos[walker].size() > 0) {
            value.pos = fields.pos[walker].str();
            value.posId = newId.pos;
        }
        if (fields.subpos[walker].size() > 0) {
            value.subpos = fields.subpos[walker].str();
            value.subposId = newId.subpos;
        }
        if (fields.conjType[walker].size() > 0) {
            value.conjType = fields.conjType[walker].str();
            value.conjTypeId = newId.conjType;
        }
        if (fields.conjForm[walker].size() > 0) {
            value.conjForm = fields.conjForm[walker].str();
            value.conjFormId = newId.conjForm;
        }

        auto res = fields.features[walker];
        auto canonic = fields.canonicForm[walker];

        auto eptr = walker.eptr();
        bool hasFeatures = eptr.isSpecial() || res.hasNext() || !canonic.empty();

        std::string feat("");
        if (hasFeatures) {
            bool output = false;
            if (!canonic.empty()) {
                feat.append("代表表記:");
                if (res.hasNext()) {
                    feat.append(" ");
                }
                output = true;
            }
            while (res.next()) {
                output = true;
                std::string key(res.key().str());
                feat.append(key);
                if (res.hasValue()) {
                    std::string::size_type pos = key.find("リダイレクト");
                    if (pos != std::string::npos) {
                        value.redirect = res.value().str();
                    }
                    feat.append(":");
                    feat.append(res.value().str());
                }
                if (res.hasNext()) {
                    feat.append(" ");
                }
            }

            if (eptr.isSpecial()) {
                auto ufld = om.valueOfUnkPlaceholder(eptr, jumanpp::jumandic::NormalizedPlaceholderIdx);
                if (ufld != 0) {
                    if (output) {
                        feat.append(" ");
                    }
                    value.featflag = ufld;
                }
            }
            value.feat = feat;
        }

        retval.push_back(value);
    }
    return retval;
}

std::string croco::Jumanpp::wakati(std::string data)
{
    std::string retval("");
    std::vector<Node> nodes = analyze(data);

    for (auto &node : nodes) {
        retval.append(node.surface);
        retval.append(" ");
    }
    retval.pop_back(); 

    return retval;
}
