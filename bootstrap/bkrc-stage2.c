/* BUNKER_CAPABILITY_JSON: {"schema_version":"bunker.self_host.capability.v1","compiler":"bkrc-self-host-bootstrap","agent_contract_version":"bunker.agent.diagnostics.v1","self_hosting_stage":"bootstrap-self-hosted-reports","ai_agent_native_diagnostics":true,"production_language_ready":false,"requires_ci_validation":true,"source_byte_spans":true,"source_excerpts":true,"structured_repair_metadata":true,"structured_parse_diagnostics":true,"diagnostic_code_registry":true,"diagnostic_phase_field":true,"diagnostic_rule_ids":true,"diagnostic_severity":true,"diagnostic_severity_counts":true,"suggested_edit_envelope":true,"import_expansion":true,"import_graph_report":true,"import_duplicate_or_cycle_summary":true,"stage1_stage2_ci_gate":true,"type_graph_report":true,"symbol_table_report":true,"name_resolver_report":true,"typecheck_report":true,"real_typechecker":true,"full_subset_type_enforcement":true,"modular_c_codegen":true,"typed_c_emission":true,"cgen_state_ref_routing":true,"hygienic_temporaries":true,"gnu_statement_expressions_locked":true,"c99_standard_portability":true,"multi_target_backend_strategy":true,"deterministic_artifact_layout":true,"supported_backends":"c, cranelift, llvm","constant_folding":true,"dead_code_elimination":true,"incremental_compilation_cache":true,"debug_info_source_mapping":true,"source_line_directives":true,"closures":true,"lambdas":true,"closure_captures":true,"code_formatter":true,"static_linter":true,"test_runner":true,"doc_generator":true,"package_manager":true,"build_cache":true,"language_server":true,"watch_mode":true,"debugger_hooks":true,"profiler_hooks":true,"coverage_tooling":true,"benchmark_tooling":true,"fuzzing_harness":true,"differential_testing":true,"property_testing":true,"stress_testing":true,"cross_platform_ci":true,"versioning_rules":true,"package_registry":true,"stdlib_documentation":true,"construct_examples":true,"migration_guides":true,"contribution_guide":true,"spec_sync":true,"roadmap_ci_gates":true,"borrow_resource_checker":true,"shell_actor_runtime":true,"declarative_view_runtime":true,"contract_verification":true,"typed_ast":true,"real_module_resolver":true,"module_cycle_path_detection":true,"visibility_boundary_enforcement":true,"semantic_validation_passes":true,"loop_control_validation":true,"unreachable_code_detection":true,"return_path_validation":true,"real_generics":true,"user_defined_adts":true,"multi_error_recovery":true,"multi_error_parse_recovery":true,"parse_recovery_synchronization":true,"diagnostic_codes":[{"code":"BKR_SELF_PARSE","rule_id":"BKR_SELF_PARSE","phase":"parse","category":"syntax","description":"Parse error with expected and actual token details."},{"code":"BKR_SELF_IMPORT_PATH","rule_id":"BKR_SELF_IMPORT_PATH","phase":"import","category":"module","description":"Invalid normalized relative import path."},{"code":"BKR_SELF_IMPORT","rule_id":"BKR_SELF_IMPORT","phase":"import","category":"module","description":"Missing imported module."},{"code":"BKR_SELF_IMPORT_CYCLE","rule_id":"BKR_SELF_IMPORT_CYCLE","phase":"import","category":"module","description":"Cyclic dependency detected in import graph."},{"code":"BKR_SELF_VISIBILITY","rule_id":"BKR_SELF_VISIBILITY","phase":"resolver","category":"visibility","description":"Attempt to access private symbol across kernel or module boundaries."},{"code":"BKR_SELF_DUPLICATE_SYMBOL","rule_id":"BKR_SELF_DUPLICATE_SYMBOL","phase":"resolver","category":"name_resolution","description":"Duplicate declaration in a scope."},{"code":"BKR_SELF_UNRESOLVED_SYMBOL","rule_id":"BKR_SELF_UNRESOLVED_SYMBOL","phase":"resolver","category":"name_resolution","description":"Unresolved identifier, function, type, struct literal, or field reference."},{"code":"BKR_SELF_TYPE_MISMATCH","rule_id":"BKR_SELF_TYPE_MISMATCH","phase":"typecheck","category":"type_system","description":"Expected/found type mismatch."},{"code":"BKR_SELF_ARITY_MISMATCH","rule_id":"BKR_SELF_ARITY_MISMATCH","phase":"typecheck","category":"type_system","description":"Function call argument count mismatch."},{"code":"BKR_SELF_ASSIGNMENT_TARGET","rule_id":"BKR_SELF_ASSIGNMENT_TARGET","phase":"typecheck","category":"type_system","description":"Invalid non-assignable assignment target."},{"code":"BKR_SELF_CONTROL_FLOW","rule_id":"BKR_SELF_CONTROL_FLOW","phase":"typecheck","category":"control_flow","description":"Invalid break or continue outside a loop."},{"code":"BKR_SELF_RETURN_PATH","rule_id":"BKR_SELF_RETURN_PATH","phase":"typecheck","category":"control_flow","description":"Non-void function can fall through without returning a value."},{"code":"BKR_SELF_UNREACHABLE_CODE","rule_id":"BKR_SELF_UNREACHABLE_CODE","phase":"typecheck","category":"control_flow","description":"Statement cannot execute because a previous statement terminates control flow."},{"code":"BKR_SELF_MATCH_PATTERN","rule_id":"BKR_SELF_MATCH_PATTERN","phase":"typecheck","category":"pattern_matching","description":"Duplicate or unreachable match pattern."},{"code":"BKR_SELF_EXHAUSTIVENESS","rule_id":"BKR_SELF_EXHAUSTIVENESS","phase":"typecheck","category":"pattern_matching","description":"Non-exhaustive match for a known finite scrutinee."},{"code":"BKR_SELF_STRUCT_LITERAL","rule_id":"BKR_SELF_STRUCT_LITERAL","phase":"typecheck","category":"data_model","description":"Invalid struct literal shape such as duplicate or missing fields."},{"code":"BKR_SELF_CONST_ASSIGNMENT","rule_id":"BKR_SELF_CONST_ASSIGNMENT","phase":"typecheck","category":"control_flow","description":"Assignment attempts to modify a top-level constant."},{"code":"BKR_SELF_AMBIGUOUS_TYPE","rule_id":"BKR_SELF_AMBIGUOUS_TYPE","phase":"typecheck","category":"type_system","description":"Expression requires a type annotation or contextual type."},{"code":"BKR_SELF_VOID_VALUE","rule_id":"BKR_SELF_VOID_VALUE","phase":"typecheck","category":"type_system","description":"Void expression is used where a value is required."},{"code":"BKR_SELF_ENTRY_POINT","rule_id":"BKR_SELF_ENTRY_POINT","phase":"typecheck","category":"program_structure","description":"Kernel entry function is missing."},{"code":"BKR_SELF_CALL_TARGET","rule_id":"BKR_SELF_CALL_TARGET","phase":"typecheck","category":"type_system","description":"Known non-function symbol is used as a call target."}],"supported_constructs":"kernel, struct, fn, const, let, fixed arrays, field access, if, else, match, Option via Some and None, Result via result_* builtins, Vec<T> handles, HashMap<K,V> handles, for ranges, while, loop, break, continue, return, primitive types, calls, casts, ternary, bitwise operators, string literals, float literals, closures, lambdas","known_limits":"byte spans only, no file span table; import graph with normalized relative path policy, exact cycle path detection, visibility boundary checking, pure typechecker, modular typed C codegen, debug source mapping, and semantic validation passes active","agent_guidance":"Use BUNKER_CAPABILITY_JSON before generating Bunker code. Use BUNKER_DIAGNOSTIC_JSON, BUNKER_RESOLVER_JSON, and BUNKER_TYPECHECK_JSON for repair tasks. Treat production_language_ready=false as requiring CI validation before release."}
*/
/* BUNKER_IMPORT_GRAPH_JSON: {"schema_version":"bunker.self_host.import_graph.v1","root_base_dir":"self-host","path_policy":"normalized_relative_forward_slash","base_directory_resolution":true,"recursive_expansion":true,"duplicate_suppression":true,"cycle_safe_expansion":true,"unique_import_count":22,"edge_count":22,"ok_edge_count":22,"missing_edge_count":0,"invalid_edge_count":0,"duplicate_edge_count":0,"duplicate_or_cycle_edge_count":0,"imports":["self-host/modules/constants.bkr","self-host/modules/kind_model.bkr","self-host/modules/ast.bkr","self-host/modules/lexer_result.bkr","self-host/modules/lexer.bkr","self-host/modules/parser_state.bkr","self-host/modules/parser.bkr","self-host/modules/cgen_state.bkr","self-host/modules/c_codegen.bkr","self-host/modules/json.bkr","self-host/modules/report_support.bkr","self-host/modules/ast_report.bkr","self-host/modules/symbol_table.bkr","self-host/modules/type_graph.bkr","self-host/modules/resolver.bkr","self-host/modules/typecheck.bkr","self-host/modules/semantic.bkr","self-host/modules/shell.bkr","self-host/modules/view.bkr","self-host/modules/verify.bkr","self-host/modules/x86_codegen.bkr","self-host/modules/driver.bkr"],"edges":[{"from_base":"self-host","requested":"modules/constants.bkr","resolved":"self-host/modules/constants.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/kind_model.bkr","resolved":"self-host/modules/kind_model.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/ast.bkr","resolved":"self-host/modules/ast.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/lexer_result.bkr","resolved":"self-host/modules/lexer_result.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/lexer.bkr","resolved":"self-host/modules/lexer.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/parser_state.bkr","resolved":"self-host/modules/parser_state.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/parser.bkr","resolved":"self-host/modules/parser.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/cgen_state.bkr","resolved":"self-host/modules/cgen_state.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/c_codegen.bkr","resolved":"self-host/modules/c_codegen.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/json.bkr","resolved":"self-host/modules/json.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/report_support.bkr","resolved":"self-host/modules/report_support.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/ast_report.bkr","resolved":"self-host/modules/ast_report.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/symbol_table.bkr","resolved":"self-host/modules/symbol_table.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/type_graph.bkr","resolved":"self-host/modules/type_graph.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/resolver.bkr","resolved":"self-host/modules/resolver.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/typecheck.bkr","resolved":"self-host/modules/typecheck.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/semantic.bkr","resolved":"self-host/modules/semantic.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/shell.bkr","resolved":"self-host/modules/shell.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/view.bkr","resolved":"self-host/modules/view.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/verify.bkr","resolved":"self-host/modules/verify.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/x86_codegen.bkr","resolved":"self-host/modules/x86_codegen.bkr","status":"ok"},{"from_base":"self-host","requested":"modules/driver.bkr","resolved":"self-host/modules/driver.bkr","status":"ok"}],"has_duplicate_or_cycle_import":false,"has_invalid_import":false,"invalid_import":"","has_missing_import":false,"missing_import":""}
*/
/* BUNKER_AST_JSON: {"schema_version":"bunker.self_host.ast.v1","representation":"bootstrap_vec_i64","source_byte_spans":true,"complete_tree":false,"truncated":true,"root":{"kind":"kernel","name":"BunkerCompiler","entry":"main","source_start":178,"source_end":955921,"span_known":true},"summary":{"source_bytes":955922,"source_lines":21628,"item_count":1816,"function_count":1600,"struct_count":60,"enum_count":7,"const_count":149},"items":[],"tree":{"kind":"kernel"}}
*/
/* BUNKER_TYPE_GRAPH_JSON: {"schema_version":"bunker.self_host.type_graph.v1","representation":"bootstrap_codegen_inference","complete":false,"declared_types":false,"local_inference":false,"truncated":true,"known_limits":"Derived from declarations plus bootstrap C codegen inference; no real Bunker typechecker, generic graph, trait constraints, exhaustiveness graph, or cross-module type graph yet. Detail arrays are omitted when interned names exceed AST_REPORT_FULL_WALK_NAME_LIMIT.","summary":{"function_count":1600,"struct_count":60,"const_count":149},"structs":[],"constants":[],"functions":[]}
*/
/* BUNKER_SYMBOL_TABLE_JSON: {"schema_version":"bunker.self_host.symbol_table.v1","representation":"bootstrap_ast_walk","complete":false,"declarations":false,"references":false,"truncated":true,"scope_model":"bootstrap kernel/function/struct scopes paired with BUNKER_RESOLVER_JSON validation","known_limits":"Derived from AST names and paired with BUNKER_RESOLVER_JSON for bootstrap duplicate/unresolved diagnostics; imports, visibility, overloads, and related definition-use spans are not complete yet. Full declaration/reference tables are omitted when interned names exceed AST_REPORT_FULL_WALK_NAME_LIMIT so stage1 compile of bkrc stays inside runner memory.","resolver_report":"BUNKER_RESOLVER_JSON","summary":{"interned_name_count":3035,"function_count":1600,"struct_count":60,"const_count":149},"declaration_table":[],"reference_table":[]}
*/
/* BUNKER_RESOLVER_JSON: {"schema_version":"bunker.self_host.resolver.v1","representation":"bootstrap_name_resolver","complete":true,"truncated":true,"duplicate_detection":true,"unresolved_detection":true,"visibility_checking":true,"import_graph_awareness":true,"cross_file_definitions":true,"related_declarations":true,"structured_repair_metadata":true,"diagnostic_phase_field":true,"diagnostic_rule_ids":true,"diagnostic_severity":true,"diagnostic_severity_counts":true,"suggested_edit_envelope":true,"has_diagnostics":false,"diagnostic_count":0,"error_count":0,"warning_count":0,"scope_model":"kernel globals plus function/block/pattern binding scopes using interned names with visibility boundaries","known_limits":"Resolver validates duplicate declarations, unresolved identifiers, calls, struct types, struct literals, and struct literal fields with related declaration span objects; import visibility boundaries and cross-file definition origins verified.","diagnostics":[]}
*/
/* BUNKER_TYPECHECK_JSON: {"schema_version":"bunker.self_host.typecheck.v1","representation":"typecheck_pass","complete":true,"truncated":true,"annotation_checks":true,"return_checks":true,"condition_checks":true,"call_argument_checks":true,"call_arity_checks":true,"call_target_checks":true,"builtin_arity_checks":true,"builtin_argument_type_checks":true,"entry_point_checks":true,"entry_signature_checks":true,"assignment_target_checks":true,"const_assignment_checks":true,"struct_field_value_checks":true,"struct_field_shape_checks":true,"ambiguous_empty_array_checks":true,"ambiguous_none_checks":true,"ambiguous_result_constructor_checks":true,"ambiguous_collection_constructor_checks":true,"index_base_type_checks":true,"index_type_checks":true,"binary_operand_checks":true,"unary_operand_checks":true,"field_access_base_checks":true,"ternary_branch_checks":true,"match_arm_type_checks":true,"match_pattern_type_checks":true,"match_pattern_semantic_checks":true,"bool_match_exhaustiveness_checks":true,"option_match_exhaustiveness_checks":true,"result_match_exhaustiveness_checks":true,"enum_match_exhaustiveness_checks":true,"scalar_match_exhaustiveness_checks":true,"finite_match_redundancy_checks":true,"array_element_type_checks":true,"loop_control_checks":true,"return_path_checks":true,"unreachable_code_checks":true,"semantic_validation_passes":true,"void_value_checks":true,"compound_void_value_checks":true,"full_value_context_void_checks":true,"typed_diagnostic_context":true,"structured_repair_metadata":true,"diagnostic_phase_field":true,"diagnostic_rule_ids":true,"diagnostic_severity":true,"diagnostic_severity_counts":true,"suggested_edit_envelope":true,"has_diagnostics":false,"diagnostic_count":0,"error_count":0,"warning_count":0,"known_limits":"Typecheck pass enforces declared annotations, return values and return paths, void value use, conditions, ternary branches, match patterns and arm values, array elements, loop-control context, unreachable statements, assignments, index bases, field-access bases, operands, calls, and struct literal shapes; full language subset semantic checking active.","diagnostics":[]}
*/
/* BUNKER_SEMANTIC_JSON: {"schema_version":"bunker.self_host.semantic.v1","has_diagnostics":false,"diagnostic_count":0,"error_count":0,"diagnostics":[]}
*/
/* Generated by Bunker Compiler */
#define BKR_REQUIRED_RUNTIME_ABI_MAJOR 1
#include "runtime.h"

typedef struct _v338 {
    bkr_i64 _v339;
    bkr_i64 _v340;
} _v338;

typedef struct _v341 {
    bkr_i64 _v342;
} _v341;

typedef struct _v343 {
    bkr_i64 _v319;
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v344;
    bkr_i64 _v345;
} _v343;

typedef struct _v346 {
    bkr_i64 _v342;
} _v346;

typedef struct _v347 {
    bkr_i64 _v319;
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v344;
} _v347;

typedef struct _v348 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v349;
    bkr_i64 _v350;
    bkr_i64 _v351;
} _v348;

typedef struct _v352 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v349;
    bkr_i64 _v353;
} _v352;

typedef struct _v354 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v356;
} _v354;

typedef struct _v357 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v358;
    bkr_i64 _v359;
    bkr_i64 _v356;
} _v357;

typedef struct _v360 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v361;
    bkr_i64 _v362;
} _v360;

typedef struct _v363 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v361;
    bkr_i64 _v355;
} _v363;

typedef struct _v364 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v365;
    bkr_i64 _v366;
} _v364;

typedef struct _v367 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v368;
} _v367;

typedef struct _v369 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v370;
} _v369;

typedef struct _v371 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v368;
} _v371;

typedef struct _v372 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v368;
    bkr_i64 _v373;
} _v372;

typedef struct _v374 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v375;
    bkr_i64 _v376;
    bkr_i64 _v377;
} _v374;

typedef struct _v378 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v375;
    bkr_i64 _v379;
} _v378;

typedef struct _v380 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v381;
    bkr_i64 _v382;
    bkr_i64 _v383;
    bkr_i64 _v379;
} _v380;

typedef struct _v384 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v379;
} _v384;

typedef struct _v385 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v386;
    bkr_i64 _v387;
} _v385;

typedef struct _v388 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v368;
} _v388;

typedef struct _v389 {
    bkr_i64 _v339;
    bkr_i64 _v340;
} _v389;

typedef struct _v390 {
    bkr_i64 _v339;
    bkr_i64 _v340;
} _v390;

typedef struct _v391 {
    bkr_i64 _v339;
    bkr_i64 _v340;
} _v391;

typedef struct _v392 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v375;
    bkr_i64 _v393;
    bkr_i64 _v394;
} _v392;

typedef struct _v395 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v396;
} _v395;

typedef struct _v397 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v398;
    bkr_i64 _v399;
} _v397;

typedef struct _v400 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v401;
    bkr_i64 _v402;
    bkr_i64 _v403;
} _v400;

typedef struct _v404 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v405;
    bkr_i64 _v406;
    bkr_i64 _v407;
    bkr_i64 _v408;
} _v404;

typedef struct _v409 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v365;
} _v409;

typedef struct _v410 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v411;
    bkr_i64 _v412;
    bkr_i64 _v379;
} _v410;

typedef struct _v413 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v365;
    bkr_i64 _v387;
} _v413;

typedef struct _v414 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v365;
} _v414;

typedef struct _v415 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v416;
} _v415;

typedef struct _v417 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v418;
    bkr_i64 _v419;
} _v417;

typedef struct _v420 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v421;
} _v420;

typedef struct _v422 {
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v355;
    bkr_i64 _v423;
    bkr_i64 _v424;
    bkr_i64 _v425;
} _v422;

typedef struct _v426 {
    bkr_i64 _v342;
} _v426;

typedef struct _v427 {
    bkr_i64 _v342;
} _v427;

typedef struct _v428 {
    bkr_i64 _v342;
} _v428;

typedef struct _v429 {
    bkr_i64 _v342;
} _v429;

typedef struct _v430 {
    bkr_i64 _v319;
    bkr_i64 _v339;
    bkr_i64 _v340;
    bkr_i64 _v387;
    bkr_i64 _v345;
    bkr_i64 _v431;
    bkr_i64 _v432;
} _v430;

typedef struct _v433 {
    bkr_i64 _v342;
} _v433;

typedef struct _v434 {
    bkr_i64 _v342;
} _v434;

typedef struct _v435 {
    bkr_i64 _v342;
} _v435;

typedef struct _v436 {
    bkr_i64 _v342;
} _v436;

typedef struct _v437 {
    bkr_i64 _v342;
} _v437;

typedef struct _v1190 {
    bkr_i64 _v342;
} _v1190;

typedef struct _v1249 {
    bkr_i64 _v342;
} _v1249;

typedef struct _v1547 {
    bkr_i64 _v342;
} _v1547;

typedef struct _v1912 {
    bkr_i64 _v1913;
    bkr_i64 _v613;
} _v1912;

typedef struct _v1922 {
    bkr_i64 _v423;
} _v1922;

typedef struct _v2411 {
    bkr_i64 _v425;
    bkr_str _v1212;
    bkr_i64 _v2412;
    bkr_i64 _v2015;
    bkr_i64 _v2413;
    bkr_i64 _v2415;
    bkr_i64 _v2416;
    bkr_i64 _v2417;
    bkr_i64 _v2418;
    bkr_i64 _v2419;
    bkr_i64 _v2420;
    bkr_i64 _v2421;
    bkr_i64 _v2422;
} _v2411;

typedef struct _v2500 {
    bkr_str _v386;
    bkr_str _v1212;
    bkr_str _v2501;
    bkr_i64 _v344;
} _v2500;

typedef struct _v2502 {
    bkr_i64 _v2503;
    bkr_i64 _v2504;
    bkr_i64 _v2505;
    bkr_i64 _v2506;
    bkr_i64 _v2507;
    bkr_i64 _v2508;
    bkr_i64 _v2509;
    bkr_i64 _v2510;
    bkr_bool _v2374;
    bkr_i64 _v2511;
    bkr_i64 _v2512;
} _v2502;

typedef struct _v2533 {
    bkr_i64 _v2534;
    bkr_i64 _v2535;
    bkr_i64 _v2536;
    bkr_i64 _v2537;
    bkr_i64 _v2538;
    bkr_i64 _v2539;
    bkr_i64 _v2540;
    bkr_i64 _v2541;
    bkr_i64 _v2542;
    bkr_i64 _v2543;
    bkr_i64 _v2544;
    bkr_i64 _v2545;
    bkr_i64 _v2546;
    bkr_i64 _v2547;
    bkr_str _v1363;
} _v2533;

typedef struct _v2595 {
    bkr_i64 _v2596;
    bkr_i64 _v2597;
    bkr_i64 _v2598;
} _v2595;

typedef struct _v2599 {
    bkr_str _v2600;
    bkr_i64 _v2601;
    bkr_i64 _v2602;
    bkr_bool _v2603;
    bkr_bool _v2604;
    bkr_str _v2605;
} _v2599;

typedef struct _v2642 {
    bkr_i64 _v1244;
    bkr_i64 _v425;
    bkr_i64 _v2643;
    bkr_i64 _v2644;
    bkr_i64 _v2645;
    bkr_i64 _v2646;
    bkr_i64 _v2647;
    bkr_i64 _v1553;
    bkr_i64 _v2648;
    bkr_i64 _v1554;
    bkr_i64 _v2418;
    bkr_i64 _v2649;
    bkr_i64 _v2416;
    bkr_i64 _v2650;
    bkr_i64 _v2651;
    bkr_i64 _v2652;
    bkr_i64 _v2653;
    bkr_i64 _v2413;
    bkr_i64 _v2654;
    bkr_i64 _v2655;
    bkr_i64 _v2656;
    bkr_i64 _v2657;
    bkr_i64 _v2658;
    bkr_i64 _v2659;
    bkr_i64 _v2660;
    bkr_i64 _v2661;
    bkr_i64 _v2662;
    bkr_i64 _v2663;
    bkr_i64 _v2664;
} _v2642;

static const bkr_i64 _v129 = 0;
static const bkr_i64 _v131 = 10;
static const bkr_i64 _v132 = 11;
static const bkr_i64 _v133 = 12;
static const bkr_i64 _v134 = 13;
static const bkr_i64 _v135 = 14;
static const bkr_i64 _v136 = 15;
static const bkr_i64 _v137 = 20;
static const bkr_i64 _v138 = 21;
static const bkr_i64 _v139 = 22;
static const bkr_i64 _v140 = 23;
static const bkr_i64 _v141 = 24;
static const bkr_i64 _v142 = 25;
static const bkr_i64 _v143 = 26;
static const bkr_i64 _v144 = 27;
static const bkr_i64 _v145 = 28;
static const bkr_i64 _v146 = 29;
static const bkr_i64 _v147 = 30;
static const bkr_i64 _v148 = 31;
static const bkr_i64 _v149 = 32;
static const bkr_i64 _v150 = 33;
static const bkr_i64 _v151 = 34;
static const bkr_i64 _v152 = 35;
static const bkr_i64 _v153 = 36;
static const bkr_i64 _v154 = 37;
static const bkr_i64 _v155 = 38;
static const bkr_i64 _v156 = 60;
static const bkr_i64 _v157 = 61;
static const bkr_i64 _v158 = 62;
static const bkr_i64 _v159 = 63;
static const bkr_i64 _v160 = 64;
static const bkr_i64 _v161 = 80;
static const bkr_i64 _v162 = 81;
static const bkr_i64 _v163 = 82;
static const bkr_i64 _v164 = 83;
static const bkr_i64 _v165 = 84;
static const bkr_i64 _v166 = 85;
static const bkr_i64 _v167 = 86;
static const bkr_i64 _v168 = 87;
static const bkr_i64 _v169 = 88;
static const bkr_i64 _v170 = 89;
static const bkr_i64 _v171 = 90;
static const bkr_i64 _v172 = 91;
static const bkr_i64 _v173 = 92;
static const bkr_i64 _v174 = 93;
static const bkr_i64 _v175 = 94;
static const bkr_i64 _v176 = 95;
static const bkr_i64 _v177 = 96;
static const bkr_i64 _v178 = 97;
static const bkr_i64 _v179 = 98;
static const bkr_i64 _v180 = 99;
static const bkr_i64 _v181 = 101;
static const bkr_i64 _v182 = 102;
static const bkr_i64 _v183 = 103;
static const bkr_i64 _v184 = 104;
static const bkr_i64 _v185 = 110;
static const bkr_i64 _v186 = 111;
static const bkr_i64 _v187 = 112;
static const bkr_i64 _v188 = 113;
static const bkr_i64 _v189 = 114;
static const bkr_i64 _v190 = 115;
static const bkr_i64 _v191 = 116;
static const bkr_i64 _v192 = 117;
static const bkr_i64 _v193 = 118;
static const bkr_i64 _v194 = 119;
static const bkr_i64 _v195 = 120;
static const bkr_i64 _v196 = 121;
static const bkr_i64 _v197 = 122;
static const bkr_i64 _v198 = 123;
static const bkr_i64 _v223 = 1;
static const bkr_i64 _v224 = 2;
static const bkr_i64 _v225 = 3;
static const bkr_i64 _v226 = 4;
static const bkr_i64 _v227 = 5;
static const bkr_i64 _v228 = 6;
static const bkr_i64 _v229 = 7;
static const bkr_i64 _v230 = 8;
static const bkr_i64 _v231 = 9;
static const bkr_i64 _v232 = 10;
static const bkr_i64 _v233 = 11;
static const bkr_i64 _v234 = 12;
static const bkr_i64 _v235 = 13;
static const bkr_i64 _v236 = 14;
static const bkr_i64 _v237 = 15;
static const bkr_i64 _v238 = 16;
static const bkr_i64 _v239 = 17;
static const bkr_i64 _v240 = 18;
static const bkr_i64 _v241 = 19;
static const bkr_i64 _v242 = 20;
static const bkr_i64 _v243 = 21;
static const bkr_i64 _v244 = 22;
static const bkr_i64 _v245 = 23;
static const bkr_i64 _v246 = 24;
static const bkr_i64 _v247 = 25;
static const bkr_i64 _v248 = 26;
static const bkr_i64 _v249 = 27;
static const bkr_i64 _v250 = 28;
static const bkr_i64 _v251 = 29;
static const bkr_i64 _v252 = 30;
static const bkr_i64 _v253 = 31;
static const bkr_i64 _v254 = 32;
static const bkr_i64 _v255 = 33;
static const bkr_i64 _v256 = 34;
static const bkr_i64 _v257 = 35;
static const bkr_i64 _v258 = 36;
static const bkr_i64 _v259 = 37;
static const bkr_i64 _v260 = 38;
static const bkr_i64 _v261 = 39;
static const bkr_i64 _v262 = 0;
static const bkr_i64 _v263 = 1;
static const bkr_i64 _v264 = 2;
static const bkr_i64 _v265 = 3;
static const bkr_i64 _v266 = 4;
static const bkr_i64 _v267 = 5;
static const bkr_i64 _v268 = 2147483647;
static const bkr_i64 _v269 = 1;
static const bkr_i64 _v270 = 2;
static const bkr_i64 _v271 = 2;
static const bkr_i64 _v272 = 3;
static const bkr_i64 _v273 = 512;
static const bkr_i64 _v283 = 1;
static const bkr_i64 _v284 = 2;
static const bkr_i64 _v285 = 3;
static const bkr_i64 _v286 = 4;
static const bkr_i64 _v287 = 5;
static const bkr_i64 _v288 = 6;
static const bkr_i64 _v289 = 7;
static const bkr_i64 _v290 = 8;
static const bkr_i64 _v291 = 9;
static const bkr_i64 _v292 = 10;
static const bkr_i64 _v293 = 11;
static const bkr_i64 _v302 = 0;
static const bkr_i64 _v303 = 1;
static const bkr_i64 _v304 = 2;
static const bkr_i64 _v305 = 3;
static const bkr_i64 _v306 = 4;
static const bkr_i64 _v307 = 5;
static const bkr_i64 _v308 = 6;
static const bkr_i64 _v309 = 7;
static const bkr_i64 _v310 = 8;
static const bkr_i64 _v311 = 9;
static const bkr_i64 _v312 = 10;
static const bkr_i64 _v313 = 11;
static const bkr_i64 _v314 = 12;
static const bkr_i64 _v315 = 13;
static const bkr_i64 _v316 = 99;
static const bkr_i64 _v2665 = 4194480;
static const bkr_i64 _v2666 = 6291456;
static const bkr_i64 _v2667 = 1048576;

bkr_str _v318(bkr_i64 _v319);
bkr_str _v324(bkr_i64 _v319);
bkr_bool _v325(bkr_i64 _v319);
bkr_str _v327(bkr_i64 _v319);
bkr_str _v328(bkr_i64 _v319);
bkr_str _v329(bkr_i64 _v330);
bkr_i64 _v331(bkr_i64 _v319);
bkr_bool _v332(bkr_i64 _v319);
bkr_bool _v333(bkr_i64 _v319);
bkr_bool _v334(bkr_i64 _v319);
bkr_bool _v335(bkr_i64 _v319);
bkr_bool _v336(bkr_i64 _v319);
_v341 _v445(bkr_i64 _v319);
_v341 _v451(_v341 _v452, bkr_i64 _v387);
_v341 _v454(_v341 _v452, bkr_i64 _v339, bkr_i64 _v340);
_v341 _v456(_v341 _v452, _v338 _v457);
_v430 _v458(bkr_i64 _v319, bkr_i64 _v387);
_v430 _v459(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345);
_v430 _v460(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431);
_v430 _v461(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431, bkr_i64 _v432);
bkr_i64 _v462(_v430 _v463);
_v430 _v464(bkr_i64 _v447);
_v433 _v468(bkr_i64 _v319, bkr_i64 _v387);
_v433 _v469(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345);
_v433 _v470(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431);
_v433 _v471(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431, bkr_i64 _v432);
_v433 _v472(_v433 _v473, bkr_i64 _v339, bkr_i64 _v340);
bkr_i64 _v475(bkr_i64 _v319);
bkr_i64 _v476(bkr_i64 _v447, bkr_i64 _v387);
bkr_i64 _v478(bkr_i64 _v447);
bkr_i64 _v479(bkr_i64 _v447);
_v338 _v480(bkr_i64 _v339, bkr_i64 _v340);
_v338 _v481(void);
bkr_i64 _v482(_v338 _v457);
bkr_i64 _v483(_v338 _v457);
bkr_bool _v484(_v338 _v457);
bkr_i64 _v485(bkr_i64 _v447);
bkr_i64 _v486(bkr_i64 _v447);
_v338 _v487(bkr_i64 _v447);
bkr_bool _v488(bkr_i64 _v447);
bkr_i64 _v489(bkr_i64 _v447, bkr_i64 _v339, bkr_i64 _v340);
bkr_i64 _v490(bkr_i64 _v447, _v338 _v457);
bkr_bool _v491(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v492(bkr_i64 _v447);
bkr_bool _v493(bkr_i64 _v447);
bkr_bool _v494(bkr_i64 _v447);
bkr_bool _v495(bkr_i64 _v447);
bkr_bool _v496(bkr_i64 _v447);
bkr_str _v497(bkr_i64 _v447);
bkr_bool _v498(bkr_i64 _v447);
bkr_bool _v499(bkr_i64 _v447);
bkr_bool _v500(bkr_i64 _v447);
bkr_bool _v501(bkr_i64 _v447);
bkr_bool _v502(bkr_i64 _v447);
bkr_bool _v503(bkr_i64 _v447);
bkr_bool _v504(bkr_i64 _v447);
bkr_i64 _v505(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v506(bkr_i64 _v447);
_v341 _v507(bkr_i64 _v342);
_v341 _v477(bkr_i64 _v447);
bkr_i64 _v508(_v341 _v452);
bkr_i64 _v453(_v341 _v452);
bkr_i64 _v510(_v341 _v452);
bkr_i64 _v511(_v341 _v452);
bkr_i64 _v512(_v341 _v452);
bkr_i64 _v513(_v341 _v452);
bkr_i64 _v509(bkr_i64 _v342);
_v341 _v514(bkr_i64 _v342);
bkr_i64 _v515(bkr_i64 _v516);
_v346 _v517(bkr_i64 _v342);
_v346 _v518(bkr_i64 _v516);
_v346 _v519(_v341 _v452);
bkr_i64 _v520(_v346 _v521);
bkr_i64 _v522(_v346 _v521);
bkr_bool _v523(_v346 _v521);
bkr_bool _v525(_v346 _v521);
bkr_i64 _v527(_v346 _v521);
_v343 _v528(_v346 _v521);
bkr_i64 _v530(_v346 _v521);
bkr_i64 _v532(_v346 _v521);
bkr_i64 _v533(_v346 _v521);
bkr_i64 _v534(_v346 _v521);
bkr_i64 _v535(_v346 _v521);
bkr_i64 _v536(_v346 _v521);
bkr_i64 _v537(bkr_i64 _v368);
_v426 _v538(bkr_i64 _v342);
_v426 _v539(bkr_i64 _v368);
_v426 _v540(_v341 _v452);
bkr_i64 _v541(_v426 _v542);
bkr_i64 _v543(_v426 _v542);
bkr_i64 _v544(_v426 _v542);
bkr_i64 _v545(_v426 _v542);
bkr_i64 _v546(_v426 _v542);
bkr_i64 _v548(_v426 _v542);
bkr_i64 _v549(bkr_i64 _v370);
_v427 _v550(bkr_i64 _v342);
_v427 _v551(bkr_i64 _v370);
_v427 _v552(_v341 _v452);
bkr_i64 _v553(_v427 _v554);
bkr_i64 _v555(_v427 _v554);
bkr_i64 _v556(_v427 _v554);
bkr_i64 _v557(bkr_i64 _v558);
_v428 _v559(bkr_i64 _v342);
_v428 _v560(bkr_i64 _v558);
_v428 _v561(_v341 _v452);
bkr_i64 _v562(_v428 _v563);
_v428 _v564(void);
bkr_bool _v566(_v428 _v563);
bkr_bool _v567(_v428 _v563);
bkr_i64 _v568(_v428 _v563);
bkr_i64 _v569(_v428 _v563);
_v338 _v570(_v426 _v542);
_v338 _v571(_v427 _v554);
_v338 _v572(_v428 _v563);
bkr_i64 _v573(_v426 _v542);
bkr_i64 _v575(_v427 _v554);
bkr_i64 _v576(_v428 _v563);
bkr_i64 _v577(bkr_i64 _v578);
_v429 _v579(bkr_i64 _v342);
_v429 _v580(bkr_i64 _v578);
_v429 _v581(_v341 _v452);
bkr_i64 _v582(_v429 _v583);
bkr_i64 _v584(_v429 _v583);
bkr_i64 _v585(_v429 _v583);
_v341 _v586(_v346 _v521);
_v341 _v547(_v426 _v542);
_v341 _v587(_v427 _v554);
_v341 _v588(_v428 _v563);
_v341 _v589(_v429 _v583);
bkr_i64 _v590(_v429 _v583);
bkr_i64 _v591(bkr_i64 _v463);
_v433 _v592(bkr_i64 _v342);
_v433 _v593(bkr_i64 _v463);
bkr_i64 _v594(_v433 _v473);
bkr_i64 _v474(_v433 _v473);
_v430 _v596(_v433 _v473);
bkr_i64 _v597(_v433 _v473);
bkr_i64 _v598(_v433 _v473);
bkr_i64 _v599(_v433 _v473);
bkr_i64 _v600(_v433 _v473);
bkr_i64 _v601(_v433 _v473);
bkr_i64 _v602(_v433 _v473);
bkr_i64 _v603(_v433 _v473);
bkr_i64 _v595(bkr_i64 _v342);
_v434 _v604(bkr_i64 _v342);
_v434 _v605(bkr_i64 _v606);
bkr_i64 _v607(_v434 _v608);
bkr_i64 _v609(_v434 _v608);
bkr_i64 _v610(bkr_i64 _v342);
_v435 _v611(bkr_i64 _v342);
_v435 _v612(bkr_i64 _v613);
bkr_i64 _v614(_v435 _v615);
bkr_i64 _v616(_v435 _v615);
bkr_i64 _v617(bkr_i64 _v342);
_v436 _v618(bkr_i64 _v342);
_v436 _v619(bkr_i64 _v406);
bkr_i64 _v620(_v436 _v621);
bkr_i64 _v622(_v436 _v621);
bkr_i64 _v623(bkr_i64 _v342);
_v437 _v624(bkr_i64 _v342);
_v437 _v625(bkr_i64 _v613);
bkr_i64 _v626(_v437 _v615);
bkr_i64 _v627(_v437 _v615);
bkr_i64 _v628(bkr_i64 _v342);
bkr_i64 _v629(bkr_i64 _v606);
bkr_i64 _v630(bkr_i64 _v613);
bkr_i64 _v631(bkr_i64 _v406);
bkr_i64 _v632(bkr_i64 _v613);
bkr_i64 _v633(bkr_i64 _v606, bkr_i64 _v447);
_v434 _v634(_v434 _v608, bkr_i64 _v447);
_v434 _v635(_v434 _v608, _v341 _v452);
_v434 _v636(_v434 _v608, _v426 _v542);
_v434 _v637(_v434 _v608, _v428 _v563);
_v434 _v638(_v434 _v608, _v429 _v583);
bkr_i64 _v639(bkr_i64 _v406, bkr_i64 _v463);
_v436 _v640(_v436 _v621, bkr_i64 _v463);
_v436 _v641(_v436 _v621, _v433 _v473);
bkr_i64 _v642(bkr_i64 _v613, bkr_i64 _v387);
_v435 _v643(_v435 _v615, bkr_i64 _v387);
bkr_i64 _v644(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v645(bkr_i64 _v447, bkr_i64 _v362);
_v434 _v646(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v647(bkr_i64 _v447, bkr_i64 _v362);
_v435 _v648(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v649(bkr_i64 _v447, bkr_i64 _v362);
_v436 _v650(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v651(bkr_i64 _v447, bkr_i64 _v362);
_v437 _v652(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v565(void);
bkr_bool _v524(bkr_i64 _v387);
bkr_bool _v526(bkr_i64 _v387);
bkr_i64 _v653(bkr_i64 _v387);
bkr_i64 _v654(bkr_i64 _v516);
bkr_i64 _v655(bkr_i64 _v516);
bkr_i64 _v656(bkr_i64 _v516);
bkr_i64 _v657(bkr_i64 _v516);
bkr_i64 _v658(bkr_i64 _v516);
bkr_i64 _v659(bkr_i64 _v516);
bkr_i64 _v660(bkr_i64 _v447);
_v347 _v661(_v426 _v542);
bkr_i64 _v663(_v426 _v542);
bkr_i64 _v664(_v341 _v452);
bkr_i64 _v665(bkr_i64 _v447);
bkr_i64 _v666(_v426 _v542);
bkr_i64 _v667(bkr_i64 _v447);
bkr_i64 _v668(bkr_i64 _v447);
bkr_i64 _v669(bkr_i64 _v447);
_v348 _v670(_v426 _v542);
bkr_i64 _v672(_v426 _v542);
bkr_i64 _v673(bkr_i64 _v447);
bkr_i64 _v674(bkr_i64 _v447);
bkr_i64 _v675(_v426 _v542);
bkr_i64 _v676(bkr_i64 _v447);
bkr_i64 _v677(bkr_i64 _v447);
bkr_i64 _v678(_v426 _v542);
bkr_i64 _v679(bkr_i64 _v447);
_v352 _v680(_v426 _v542);
bkr_i64 _v682(_v426 _v542);
bkr_i64 _v683(bkr_i64 _v447);
bkr_i64 _v684(bkr_i64 _v447);
bkr_i64 _v685(_v426 _v542);
bkr_i64 _v686(bkr_i64 _v447);
_v354 _v687(_v426 _v542);
bkr_i64 _v689(_v426 _v542);
bkr_i64 _v690(bkr_i64 _v447);
_v434 _v691(bkr_i64 _v447);
_v434 _v692(_v426 _v542);
bkr_i64 _v693(bkr_i64 _v447);
bkr_i64 _v694(_v426 _v542);
_v426 _v695(_v426 _v542);
bkr_i64 _v696(bkr_i64 _v447);
bkr_i64 _v697(_v426 _v542);
_v434 _v698(bkr_i64 _v447);
_v434 _v699(_v426 _v542);
bkr_i64 _v700(bkr_i64 _v447);
_v434 _v701(bkr_i64 _v447);
_v434 _v702(_v426 _v542);
bkr_i64 _v703(bkr_i64 _v447);
bkr_i64 _v704(_v426 _v542);
_v426 _v705(_v426 _v542);
bkr_i64 _v706(bkr_i64 _v447);
bkr_i64 _v707(_v426 _v542);
bkr_i64 _v708(bkr_i64 _v447);
bkr_i64 _v709(bkr_i64 _v447);
_v360 _v710(_v426 _v542);
bkr_i64 _v712(_v426 _v542);
bkr_i64 _v713(bkr_i64 _v447);
bkr_i64 _v714(bkr_i64 _v447);
bkr_i64 _v715(_v426 _v542);
bkr_i64 _v716(bkr_i64 _v447);
bkr_i64 _v717(bkr_i64 _v447);
_v363 _v718(_v426 _v542);
bkr_i64 _v720(_v426 _v542);
_v426 _v721(_v426 _v542);
bkr_i64 _v722(bkr_i64 _v447);
bkr_i64 _v723(_v426 _v542);
bkr_i64 _v724(bkr_i64 _v447);
bkr_i64 _v725(_v426 _v542);
bkr_i64 _v726(bkr_i64 _v447);
_v435 _v727(bkr_i64 _v447);
_v435 _v728(_v426 _v542);
bkr_i64 _v729(bkr_i64 _v447);
_v434 _v730(bkr_i64 _v447);
_v434 _v731(_v426 _v542);
bkr_i64 _v732(bkr_i64 _v447);
bkr_i64 _v733(bkr_i64 _v447);
bkr_i64 _v734(_v426 _v542);
bkr_i64 _v735(bkr_i64 _v447);
bkr_i64 _v736(bkr_i64 _v447);
bkr_i64 _v737(_v426 _v542);
bkr_i64 _v738(bkr_i64 _v447);
bkr_i64 _v739(bkr_i64 _v447);
bkr_i64 _v740(_v426 _v542);
bkr_i64 _v741(bkr_i64 _v447);
bkr_i64 _v742(bkr_i64 _v447);
bkr_i64 _v743(_v426 _v542);
bkr_i64 _v744(bkr_i64 _v447);
_v436 _v745(bkr_i64 _v447);
_v436 _v746(_v426 _v542);
bkr_i64 _v747(bkr_i64 _v447);
_v434 _v748(bkr_i64 _v447);
_v434 _v749(_v426 _v542);
_v435 _v750(bkr_i64 _v447);
_v435 _v751(_v426 _v542);
bkr_i64 _v752(bkr_i64 _v463);
bkr_i64 _v754(bkr_i64 _v463);
bkr_i64 _v755(bkr_i64 _v447);
_v364 _v756(_v427 _v554);
bkr_i64 _v758(_v427 _v554);
bkr_i64 _v759(bkr_i64 _v447);
bkr_i64 _v760(bkr_i64 _v447);
bkr_i64 _v761(_v427 _v554);
bkr_i64 _v762(bkr_i64 _v447);
bkr_i64 _v763(bkr_i64 _v447);
bkr_i64 _v764(_v427 _v554);
bkr_i64 _v765(bkr_i64 _v447);
bkr_i64 _v766(bkr_i64 _v447);
_v367 _v767(_v427 _v554);
bkr_i64 _v769(_v427 _v554);
bkr_i64 _v770(bkr_i64 _v447);
_v369 _v771(_v427 _v554);
bkr_i64 _v773(_v427 _v554);
_v427 _v774(_v427 _v554);
bkr_i64 _v775(bkr_i64 _v447);
_v371 _v776(_v426 _v542);
bkr_i64 _v778(_v426 _v542);
_v426 _v779(_v426 _v542);
bkr_i64 _v780(bkr_i64 _v447);
bkr_i64 _v781(bkr_i64 _v447);
bkr_i64 _v782(_v426 _v542);
bkr_i64 _v783(_v426 _v542);
_v426 _v784(_v426 _v542);
_v346 _v785(_v426 _v542);
_v374 _v786(_v427 _v554);
_v378 _v788(_v427 _v554);
_v380 _v790(_v427 _v554);
_v384 _v792(_v427 _v554);
_v385 _v794(_v427 _v554);
_v388 _v796(_v427 _v554);
_v389 _v798(_v427 _v554);
_v390 _v800(_v427 _v554);
_v391 _v802(_v429 _v583);
_v392 _v804(_v426 _v542);
_v395 _v806(_v426 _v542);
_v400 _v808(_v426 _v542);
_v404 _v810(_v426 _v542);
_v409 _v812(_v341 _v452);
_v410 _v814(_v428 _v563);
_v413 _v816(_v428 _v563);
_v414 _v818(_v341 _v452);
_v415 _v820(_v428 _v563);
_v417 _v822(_v428 _v563);
_v422 _v824(_v341 _v452);
bkr_i64 _v826(bkr_i64 _v447);
bkr_i64 _v827(bkr_i64 _v447);
bkr_i64 _v828(_v427 _v554);
bkr_i64 _v829(bkr_i64 _v447);
_v429 _v830(_v427 _v554);
bkr_i64 _v831(bkr_i64 _v447);
bkr_i64 _v832(bkr_i64 _v447);
bkr_i64 _v833(_v427 _v554);
bkr_i64 _v834(bkr_i64 _v447);
bkr_i64 _v835(_v427 _v554);
bkr_i64 _v836(bkr_i64 _v447);
bkr_i64 _v837(bkr_i64 _v447);
bkr_i64 _v838(_v427 _v554);
bkr_i64 _v839(bkr_i64 _v447);
bkr_i64 _v840(bkr_i64 _v447);
bkr_i64 _v841(_v427 _v554);
bkr_i64 _v842(bkr_i64 _v447);
bkr_i64 _v843(_v427 _v554);
bkr_i64 _v844(bkr_i64 _v447);
_v429 _v845(_v427 _v554);
bkr_i64 _v846(bkr_i64 _v447);
_v429 _v847(_v427 _v554);
bkr_i64 _v848(bkr_i64 _v447);
bkr_i64 _v849(bkr_i64 _v447);
bkr_i64 _v850(_v427 _v554);
bkr_i64 _v851(bkr_i64 _v447);
_v429 _v852(_v427 _v554);
bkr_i64 _v853(bkr_i64 _v447);
bkr_i64 _v854(bkr_i64 _v447);
bkr_i64 _v855(_v427 _v554);
bkr_i64 _v856(bkr_i64 _v447);
bkr_i64 _v857(bkr_i64 _v447);
bkr_i64 _v858(_v427 _v554);
bkr_i64 _v859(bkr_i64 _v447);
bkr_i64 _v860(bkr_i64 _v447);
bkr_i64 _v861(_v427 _v554);
bkr_i64 _v862(bkr_i64 _v447);
bkr_i64 _v863(_v341 _v452);
bkr_i64 _v864(bkr_i64 _v447);
bkr_i64 _v865(bkr_i64 _v447);
bkr_i64 _v866(_v341 _v452);
_v346 _v867(_v341 _v452);
bkr_i64 _v868(bkr_i64 _v447);
bkr_i64 _v869(_v428 _v563);
bkr_i64 _v870(bkr_i64 _v447);
_v434 _v871(bkr_i64 _v447);
_v434 _v872(_v428 _v563);
bkr_i64 _v873(bkr_i64 _v447);
bkr_i64 _v874(bkr_i64 _v447);
bkr_i64 _v875(_v428 _v563);
bkr_i64 _v876(bkr_i64 _v447);
_v429 _v877(_v428 _v563);
bkr_i64 _v878(bkr_i64 _v447);
bkr_i64 _v879(_v428 _v563);
bkr_i64 _v880(bkr_i64 _v447);
bkr_i64 _v881(bkr_i64 _v447);
bkr_i64 _v882(_v428 _v563);
bkr_i64 _v883(bkr_i64 _v447);
bkr_i64 _v884(bkr_i64 _v447);
bkr_i64 _v885(_v428 _v563);
bkr_i64 _v886(bkr_i64 _v447);
bkr_i64 _v887(_v428 _v563);
bkr_i64 _v888(bkr_i64 _v447);
_v434 _v889(bkr_i64 _v447);
_v434 _v890(_v428 _v563);
bkr_i64 _v891(bkr_i64 _v447);
bkr_i64 _v892(_v341 _v452);
bkr_i64 _v893(bkr_i64 _v447);
bkr_i64 _v894(bkr_i64 _v447);
bkr_i64 _v895(_v341 _v452);
_v346 _v896(_v341 _v452);
bkr_i64 _v897(bkr_i64 _v447);
_v434 _v898(bkr_i64 _v447);
_v434 _v899(_v341 _v452);
bkr_i64 _v900(bkr_i64 _v447);
bkr_i64 _v901(_v341 _v452);
bkr_i64 _v902(bkr_i64 _v447);
bkr_i64 _v904(_v341 _v452);
_v437 _v903(bkr_i64 _v447);
_v437 _v905(_v341 _v452);
bkr_i64 _v906(bkr_i64 _v606);
bkr_i64 _v907(_v434 _v608);
bkr_i64 _v908(bkr_i64 _v606, bkr_i64 _v362);
bkr_i64 _v909(_v434 _v608, bkr_i64 _v362);
bkr_i64 _v911(bkr_i64 _v606, bkr_i64 _v362);
bkr_i64 _v910(_v434 _v608, bkr_i64 _v362);
_v341 _v912(bkr_i64 _v606, bkr_i64 _v362);
_v341 _v913(_v434 _v608, bkr_i64 _v362);
_v428 _v914(_v434 _v608, bkr_i64 _v362);
bkr_i64 _v915(bkr_i64 _v613);
bkr_i64 _v916(_v435 _v615);
bkr_i64 _v917(bkr_i64 _v613, bkr_i64 _v362);
bkr_i64 _v918(_v435 _v615, bkr_i64 _v362);
bkr_i64 _v919(bkr_i64 _v406);
bkr_i64 _v920(_v436 _v621);
bkr_i64 _v921(bkr_i64 _v406, bkr_i64 _v362);
bkr_i64 _v922(_v436 _v621, bkr_i64 _v362);
bkr_i64 _v923(_v436 _v621, bkr_i64 _v362);
_v433 _v924(bkr_i64 _v406, bkr_i64 _v362);
_v433 _v925(_v436 _v621, bkr_i64 _v362);
bkr_i64 _v926(bkr_i64 _v0);
bkr_i64 _v927(bkr_i64 _v0, bkr_i64 _v362);
bkr_i64 _v928(bkr_i64 _v0, bkr_i64 _v362);
bkr_i64 _v929(bkr_i64 _v930);
bkr_i64 _v931(bkr_i64 _v930, bkr_i64 _v362);
bkr_i64 _v932(bkr_i64 _v933);
bkr_i64 _v934(bkr_i64 _v933, bkr_i64 _v362);
bkr_i64 _v935(bkr_i64 _v936);
bkr_i64 _v937(bkr_i64 _v936, bkr_i64 _v362);
bkr_i64 _v938(bkr_i64 _v936, bkr_i64 _v362);
bkr_i64 _v939(bkr_i64 _v940);
bkr_i64 _v941(bkr_i64 _v940, bkr_i64 _v362);
bkr_i64 _v942(bkr_i64 _v940, bkr_i64 _v362);
bkr_i64 _v943(bkr_i64 _v944);
bkr_i64 _v945(bkr_i64 _v944, bkr_i64 _v362);
bkr_i64 _v946(bkr_i64 _v944, bkr_i64 _v362);
bkr_i64 _v947(bkr_i64 _v944, bkr_i64 _v362);
bkr_i64 _v948(bkr_i64 _v447);
bkr_i64 _v949(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v950(bkr_i64 _v447, bkr_i64 _v362);
bkr_i64 _v951(bkr_i64 _v447, bkr_i64 _v362);
_v343 _v952(bkr_i64 _v319);
_v343 _v953(bkr_i64 _v954, bkr_i64 _v955);
_v343 _v956(bkr_i64 _v355);
_v343 _v957(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345);
bkr_i64 _v958(_v343 _v959);
_v343 _v529(bkr_i64 _v447);
_v346 _v960(bkr_i64 _v319);
bkr_i64 _v961(bkr_i64 _v319);
_v346 _v962(bkr_i64 _v954, bkr_i64 _v955);
bkr_i64 _v963(bkr_i64 _v954, bkr_i64 _v955);
_v346 _v964(bkr_i64 _v355);
bkr_i64 _v965(bkr_i64 _v355);
_v346 _v966(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345);
bkr_i64 _v967(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345);
bkr_i64 _v968(bkr_i64 _v319, bkr_i64 _v387);
bkr_i64 _v969(bkr_i64 _v463);
bkr_i64 _v970(bkr_i64 _v463);
bkr_i64 _v971(bkr_i64 _v463, bkr_i64 _v339, bkr_i64 _v340);
_v404 _v972(bkr_i64 _v405, bkr_i64 _v406, bkr_i64 _v407, bkr_i64 _v408);
bkr_i64 _v973(_v404 _v368);
_v404 _v811(bkr_i64 _v447);
_v426 _v974(_v426 _v975, _v436 _v621, _v434 _v976, _v435 _v977);
bkr_i64 _v978(bkr_i64 _v405, bkr_i64 _v406, bkr_i64 _v407);
_v347 _v980(bkr_i64 _v319, bkr_i64 _v344);
bkr_i64 _v981(_v347 _v982);
_v347 _v662(bkr_i64 _v447);
_v426 _v983(bkr_i64 _v319, bkr_i64 _v344);
_v426 _v984(bkr_i64 _v387);
bkr_i64 _v985(bkr_i64 _v387);
_v426 _v986(bkr_str _v387);
bkr_i64 _v987(bkr_str _v387);
_v426 _v988(bkr_i64 _v387);
bkr_i64 _v989(bkr_i64 _v387);
_v426 _v990(bkr_str _v387);
bkr_i64 _v991(bkr_str _v387);
_v395 _v992(bkr_i64 _v396);
bkr_i64 _v993(_v395 _v368);
_v395 _v807(bkr_i64 _v447);
_v426 _v994(_v434 _v995);
bkr_i64 _v996(bkr_i64 _v396);
_v397 _v997(bkr_i64 _v398, bkr_i64 _v399);
bkr_i64 _v998(_v397 _v368);
_v397 _v999(bkr_i64 _v447);
_v426 _v1000(_v426 _v1001, bkr_i64 _v399);
bkr_i64 _v1002(bkr_i64 _v398, bkr_i64 _v399);
_v400 _v1003(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402);
_v400 _v1004(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402, bkr_i64 _v403);
bkr_i64 _v1005(_v400 _v368);
_v400 _v809(bkr_i64 _v447);
bkr_i64 _v1006(_v426 _v542);
_v426 _v1007(bkr_i64 _v355, _v435 _v1008, _v434 _v1009, bkr_i64 _v403);
_v426 _v1010(bkr_i64 _v355, _v435 _v1008, _v434 _v1009);
bkr_i64 _v1011(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402);
_v354 _v1012(bkr_i64 _v355, bkr_i64 _v356);
bkr_i64 _v1013(_v354 _v1014);
_v354 _v688(bkr_i64 _v447);
_v426 _v1015(bkr_i64 _v355, _v434 _v1016);
bkr_i64 _v1017(bkr_i64 _v355, bkr_i64 _v356);
_v357 _v1018(bkr_i64 _v358, bkr_i64 _v359, bkr_i64 _v356);
bkr_i64 _v1019(_v357 _v1014);
_v357 _v1020(bkr_i64 _v447);
_v426 _v1021(_v426 _v1022, bkr_i64 _v359, _v434 _v1016);
bkr_i64 _v1023(bkr_i64 _v358, bkr_i64 _v359, bkr_i64 _v356);
_v426 _v1024(bkr_i64 _v355);
bkr_i64 _v1025(_v426 _v1026);
bkr_i64 _v1027(bkr_i64 _v355);
_v352 _v1028(bkr_i64 _v349, bkr_i64 _v353);
bkr_i64 _v1029(_v352 _v1030);
_v352 _v681(bkr_i64 _v447);
_v426 _v1031(bkr_i64 _v349, _v426 _v1032);
bkr_i64 _v1033(bkr_i64 _v349, bkr_i64 _v353);
_v360 _v1034(bkr_i64 _v361, bkr_i64 _v362);
bkr_i64 _v1035(_v360 _v1036);
_v360 _v711(bkr_i64 _v447);
_v426 _v1037(_v426 _v1038, _v426 _v1039);
bkr_i64 _v1040(bkr_i64 _v361, bkr_i64 _v362);
_v363 _v1041(bkr_i64 _v361, bkr_i64 _v355);
bkr_i64 _v1042(_v363 _v1043);
_v363 _v719(bkr_i64 _v447);
_v426 _v1044(_v426 _v1038, bkr_i64 _v1045);
bkr_i64 _v1046(bkr_i64 _v361, bkr_i64 _v1045);
_v348 _v1047(bkr_i64 _v349, bkr_i64 _v350, bkr_i64 _v351);
bkr_i64 _v1048(_v348 _v1049);
_v348 _v671(bkr_i64 _v447);
_v426 _v1050(bkr_i64 _v349, _v426 _v1051, _v426 _v1052);
bkr_i64 _v1053(bkr_i64 _v349, bkr_i64 _v350, bkr_i64 _v351);
_v392 _v1054(bkr_i64 _v375, bkr_i64 _v393, bkr_i64 _v394);
bkr_i64 _v1055(_v392 _v368);
_v392 _v805(bkr_i64 _v447);
_v426 _v1056(_v426 _v1057, _v426 _v1058, _v426 _v1059);
bkr_i64 _v1060(bkr_i64 _v375, bkr_i64 _v393, bkr_i64 _v394);
_v364 _v1061(bkr_i64 _v355, bkr_i64 _v365, bkr_i64 _v366);
bkr_i64 _v1062(_v364 _v370);
_v364 _v757(bkr_i64 _v447);
_v427 _v1063(bkr_i64 _v355, bkr_i64 _v516, bkr_i64 _v366);
_v427 _v1064(_v427 _v554);
bkr_bool _v1066(_v427 _v554);
bkr_i64 _v1067(bkr_i64 _v355, bkr_i64 _v516, bkr_i64 _v366);
_v367 _v1068(bkr_i64 _v368);
bkr_i64 _v1069(_v367 _v370);
_v367 _v768(bkr_i64 _v447);
_v427 _v1070(bkr_i64 _v368);
bkr_i64 _v1071(bkr_i64 _v368);
_v369 _v1072(bkr_i64 _v370);
bkr_i64 _v1073(_v369 _v370);
_v369 _v772(bkr_i64 _v447);
_v427 _v1074(_v427 _v370);
bkr_i64 _v1075(bkr_i64 _v370);
_v371 _v1076(bkr_i64 _v368);
bkr_i64 _v1077(_v371 _v1078);
_v371 _v777(bkr_i64 _v447);
_v426 _v1079(_v426 _v368);
bkr_i64 _v1080(bkr_i64 _v368);
_v372 _v1081(bkr_i64 _v368, bkr_i64 _v373);
bkr_i64 _v1082(_v372 _v1083);
_v372 _v1084(bkr_i64 _v447);
_v426 _v1085(_v426 _v368, _v346 _v373);
bkr_i64 _v1086(bkr_i64 _v368, bkr_i64 _v373);
_v389 _v1087(void);
bkr_i64 _v1088(_v389 _v370);
_v389 _v799(bkr_i64 _v447);
_v427 _v1089(void);
bkr_i64 _v1090(void);
_v390 _v1091(void);
bkr_i64 _v1092(_v390 _v370);
_v390 _v801(bkr_i64 _v447);
_v427 _v1093(void);
bkr_i64 _v1094(void);
_v385 _v1095(bkr_i64 _v386, bkr_i64 _v387);
bkr_i64 _v1096(_v385 _v370);
_v385 _v795(bkr_i64 _v447);
_v427 _v1097(_v426 _v1098, _v426 _v1099);
bkr_i64 _v1100(bkr_i64 _v386, bkr_i64 _v387);
_v388 _v1101(bkr_i64 _v368);
bkr_i64 _v1102(_v388 _v370);
_v388 _v797(bkr_i64 _v447);
_v427 _v1103(_v426 _v542);
bkr_i64 _v1104(bkr_i64 _v368);
_v391 _v1105(void);
bkr_i64 _v1106(_v391 _v578);
_v391 _v803(bkr_i64 _v447);
_v429 _v1107(void);
bkr_i64 _v1108(void);
bkr_i64 _v1109(bkr_i64 _v578);
bkr_i64 _v1110(bkr_i64 _v578, bkr_i64 _v362);
_v427 _v1111(_v429 _v583, bkr_i64 _v362);
bkr_i64 _v1112(bkr_i64 _v578);
_v429 _v1113(_v429 _v583, _v427 _v554);
bkr_i64 _v1114(bkr_i64 _v578, bkr_i64 _v370);
_v429 _v1115(_v427 _v554);
bkr_i64 _v1116(bkr_i64 _v370);
_v374 _v1117(bkr_i64 _v375, bkr_i64 _v376, bkr_i64 _v377);
bkr_i64 _v1118(_v374 _v370);
_v374 _v787(bkr_i64 _v447);
_v427 _v1119(_v426 _v1057, _v429 _v1120, bkr_i64 _v377);
bkr_i64 _v1121(bkr_i64 _v375, bkr_i64 _v376, bkr_i64 _v377);
_v380 _v1122(bkr_i64 _v355, bkr_i64 _v381, bkr_i64 _v382, bkr_i64 _v383, bkr_i64 _v379);
bkr_i64 _v1123(_v380 _v370);
_v380 _v791(bkr_i64 _v447);
_v427 _v1124(bkr_i64 _v355, _v426 _v1125, _v426 _v1126, bkr_i64 _v383, _v429 _v1127);
bkr_i64 _v1128(bkr_i64 _v355, bkr_i64 _v381, bkr_i64 _v382, bkr_i64 _v383, bkr_i64 _v379);
_v378 _v1129(bkr_i64 _v375, bkr_i64 _v379);
bkr_i64 _v1130(_v378 _v370);
_v378 _v789(bkr_i64 _v447);
_v427 _v1131(_v426 _v1057, _v429 _v1127);
bkr_i64 _v1132(bkr_i64 _v375, bkr_i64 _v379);
_v384 _v1133(bkr_i64 _v379);
bkr_i64 _v1134(_v384 _v370);
_v384 _v793(bkr_i64 _v447);
_v427 _v1135(_v429 _v1127);
bkr_i64 _v1136(bkr_i64 _v379);
_v409 _v1137(bkr_i64 _v355, bkr_i64 _v365);
bkr_i64 _v1138(_v409 _v1139);
_v409 _v813(bkr_i64 _v447);
_v341 _v1140(bkr_i64 _v355, _v346 _v521);
bkr_i64 _v1141(bkr_i64 _v355, bkr_i64 _v516);
_v410 _v1142(bkr_i64 _v355, bkr_i64 _v411, bkr_i64 _v412, bkr_i64 _v379);
bkr_i64 _v1143(_v410 _v558);
_v410 _v815(bkr_i64 _v447);
_v428 _v1144(bkr_i64 _v355, _v434 _v1145, bkr_i64 _v1146, _v429 _v1127);
bkr_i64 _v1147(bkr_i64 _v355, bkr_i64 _v411, bkr_i64 _v1146, bkr_i64 _v379);
_v413 _v1148(bkr_i64 _v355, bkr_i64 _v365, bkr_i64 _v387);
bkr_i64 _v1149(_v413 _v558);
_v413 _v817(bkr_i64 _v447);
_v428 _v1150(bkr_i64 _v355, bkr_i64 _v516, bkr_i64 _v387);
bkr_i64 _v1151(bkr_i64 _v355, bkr_i64 _v516, bkr_i64 _v387);
_v414 _v1152(bkr_i64 _v355, bkr_i64 _v365);
bkr_i64 _v1153(_v414 _v1154);
_v414 _v819(bkr_i64 _v447);
_v341 _v1155(bkr_i64 _v1045, _v346 _v1156);
bkr_i64 _v1157(bkr_i64 _v1045, bkr_i64 _v1158);
_v415 _v1159(bkr_i64 _v355, bkr_i64 _v416);
bkr_i64 _v1160(_v415 _v558);
_v415 _v821(bkr_i64 _v447);
_v428 _v1161(bkr_i64 _v355, _v434 _v1162);
_v417 _v1163(bkr_i64 _v355, bkr_i64 _v418, bkr_i64 _v419);
bkr_i64 _v1164(_v417 _v558);
_v417 _v823(bkr_i64 _v447);
_v428 _v1165(bkr_i64 _v355, _v435 _v1166, _v435 _v1167);
bkr_i64 _v1168(_v428 _v563);
_v435 _v1169(_v428 _v563);
_v435 _v1170(_v428 _v563);
bkr_i64 _v1171(_v428 _v563);
bkr_i64 _v1173(_v428 _v563);
_v420 _v1175(bkr_i64 _v355, bkr_i64 _v421);
bkr_i64 _v1176(_v420 _v558);
_v420 _v1177(bkr_i64 _v447);
_v428 _v1178(bkr_i64 _v355, _v346 _v1098);
bkr_i64 _v1179(bkr_i64 _v355, bkr_i64 _v373);
bkr_i64 _v1180(_v428 _v563);
bkr_i64 _v1181(_v428 _v563);
bkr_i64 _v1182(bkr_i64 _v355, bkr_i64 _v416);
_v422 _v1183(bkr_i64 _v355, bkr_i64 _v423, bkr_i64 _v424, bkr_i64 _v425);
bkr_i64 _v1184(_v422 _v0);
_v422 _v825(bkr_i64 _v447);
_v341 _v1185(bkr_i64 _v355, _v434 _v1186, bkr_i64 _v1187, _v437 _v1188);
bkr_i64 _v1189(bkr_i64 _v355, bkr_i64 _v423, bkr_i64 _v1187, bkr_i64 _v425);
bkr_i64 _v1191(bkr_i64 _v1192, bkr_i64 _v425, bkr_i64 _v613, bkr_i64 _v1193);
_v1190 _v1195(bkr_i64 _v1192, bkr_i64 _v425, bkr_i64 _v613, bkr_i64 _v1193);
_v1190 _v1197(bkr_i64 _v1196);
bkr_i64 _v1194(_v1190 _v1198);
bkr_i64 _v1199(bkr_i64 _v1196);
bkr_i64 _v1200(_v1190 _v1198);
bkr_i64 _v1201(bkr_i64 _v1196);
bkr_i64 _v1202(_v1190 _v1198);
bkr_i64 _v1203(bkr_i64 _v1196);
bkr_i64 _v1204(_v1190 _v1198);
bkr_i64 _v1205(bkr_i64 _v1196);
bkr_i64 _v1206(_v1190 _v1198);
bkr_bool _v1207(bkr_i64 _v1208);
bkr_bool _v1209(bkr_i64 _v1208);
bkr_bool _v1210(bkr_i64 _v1208);
bkr_i64 _v1211(bkr_str _v1212, bkr_i64 _v1213);
bkr_i64 _v1219(bkr_i64 _v1208);
bkr_i64 _v1220(bkr_str _v1212, bkr_i64 _v1213, bkr_i64 _v1221);
bkr_i64 _v1225(bkr_i64 _v425, bkr_str _v1226);
bkr_i64 _v1227(bkr_str _v1212);
_v1190 _v1228(bkr_str _v1212);
bkr_i64 _v1250(bkr_i64 _v1251);
_v1249 _v1253(_v1190 _v1251);
_v1249 _v1258(bkr_i64 _v1254);
bkr_i64 _v1252(_v1249 _v1259);
bkr_i64 _v1260(bkr_i64 _v1261);
bkr_i64 _v1262(_v1249 _v1259);
bkr_i64 _v1263(bkr_i64 _v1261);
bkr_i64 _v1264(_v1249 _v1259);
bkr_i64 _v1265(bkr_i64 _v1261);
bkr_i64 _v1266(_v1249 _v1259);
bkr_i64 _v1267(bkr_i64 _v1261);
bkr_i64 _v1268(_v1249 _v1259);
bkr_i64 _v1269(bkr_i64 _v1261);
bkr_i64 _v1270(_v1249 _v1259);
bkr_i64 _v1271(bkr_i64 _v1261, bkr_i64 _v1213);
_v1249 _v1272(_v1249 _v1259, bkr_i64 _v1213);
bkr_i64 _v1273(bkr_i64 _v1261, bkr_i64 _v1274);
_v1249 _v1275(_v1249 _v1259, bkr_i64 _v1274);
bkr_i64 _v1276(bkr_i64 _v1261, bkr_i64 _v1213);
_v1249 _v1277(_v1249 _v1259, bkr_i64 _v1213);
bkr_i64 _v1278(bkr_i64 _v1261, bkr_i64 _v1279);
_v1249 _v1280(_v1249 _v1259, bkr_i64 _v1279);
bkr_i64 _v1281(bkr_i64 _v1261, bkr_i64 _v1282);
_v1249 _v1283(_v1249 _v1259, bkr_i64 _v1282);
bkr_i64 _v1284(bkr_i64 _v1261);
bkr_i64 _v1285(_v1249 _v1259);
bkr_i64 _v1286(bkr_i64 _v1261);
bkr_i64 _v1287(_v1249 _v1259);
bkr_i64 _v1288(bkr_i64 _v1261, bkr_i64 _v1289);
bkr_i64 _v1290(_v1249 _v1259, bkr_i64 _v1289);
bkr_i64 _v1291(bkr_i64 _v1261);
bkr_i64 _v1292(_v1249 _v1259);
bkr_bool _v1293(bkr_i64 _v1261, bkr_i64 _v1279);
bkr_bool _v1294(_v1249 _v1259, bkr_i64 _v1279);
bkr_i64 _v1296(bkr_i64 _v1261, bkr_i64 _v1279);
_v1249 _v1295(_v1249 _v1259, bkr_i64 _v1279);
bkr_str _v1302(bkr_i64 _v1261, bkr_i64 _v1036);
bkr_str _v1303(_v1249 _v1259, bkr_i64 _v1036);
bkr_i64 _v1304(_v1249 _v1259, bkr_str _v1305);
bkr_i64 _v1306(bkr_i64 _v1261, bkr_i64 _v1036);
bkr_i64 _v1307(_v1249 _v1259, bkr_i64 _v1036);
bkr_str _v1308(bkr_i64 _v1261, bkr_i64 _v1036);
bkr_str _v1309(_v1249 _v1259, bkr_i64 _v1036);
bkr_bool _v1310(bkr_i64 _v1261);
bkr_bool _v1311(_v1249 _v1259);
bkr_i64 _v1312(bkr_i64 _v1261);
bkr_i64 _v1299(_v1249 _v1259);
bkr_i64 _v1313(bkr_i64 _v1261);
bkr_i64 _v1314(_v1249 _v1259);
bkr_i64 _v1315(bkr_i64 _v1261);
bkr_i64 _v1316(_v1249 _v1259);
bkr_i64 _v1317(_v1249 _v1259);
bkr_i64 _v1318(_v1249 _v1259, bkr_i64 _v1036);
bkr_i64 _v1319(_v1249 _v1259, bkr_i64 _v1036);
bkr_i64 _v1320(_v1249 _v1259, bkr_i64 _v1036);
bkr_str _v1321(bkr_i64 _v1322);
bkr_bool _v1323(bkr_i64 _v1322);
bkr_i64 _v1324(bkr_i64 _v1261, bkr_i64 _v1213);
bkr_i64 _v1325(_v1249 _v1261, bkr_i64 _v1213);
bkr_i64 _v1326(bkr_i64 _v1261, bkr_i64 _v1213);
bkr_i64 _v1327(_v1249 _v1261, bkr_i64 _v1213);
bkr_i64 _v1328(_v1249 _v1261);
bkr_i64 _v1329(_v1249 _v1261);
bkr_i64 _v1330(_v1249 _v1261, bkr_i64 _v339);
_v338 _v1331(_v1249 _v1261, bkr_i64 _v339);
_v341 _v1332(_v1249 _v1261, _v341 _v452, bkr_i64 _v339);
_v341 _v1333(_v341 _v452, bkr_i64 _v339, bkr_i64 _v340);
_v346 _v1334(_v1249 _v1261, _v346 _v521, bkr_i64 _v339);
_v426 _v1335(_v1249 _v1261, _v426 _v542, bkr_i64 _v339);
_v426 _v1336(_v426 _v542, bkr_i64 _v339, bkr_i64 _v340);
_v427 _v1337(_v1249 _v1261, _v427 _v554, bkr_i64 _v339);
_v427 _v1338(_v427 _v554, bkr_i64 _v339, bkr_i64 _v340);
_v428 _v1339(_v1249 _v1261, _v428 _v563, bkr_i64 _v339);
_v429 _v1340(_v1249 _v1261, _v429 _v583, bkr_i64 _v339);
bkr_i64 _v1341(_v1249 _v1261, bkr_i64 _v447, bkr_i64 _v339);
_v433 _v1343(_v1249 _v1261, _v433 _v473, bkr_i64 _v339);
bkr_i64 _v1344(_v1249 _v1261, bkr_i64 _v463, bkr_i64 _v339);
bkr_i64 _v1342(_v341 _v452);
bkr_i64 _v1346(_v346 _v521);
bkr_i64 _v1347(_v426 _v542);
bkr_i64 _v1348(_v427 _v554);
bkr_i64 _v1349(_v428 _v563);
bkr_i64 _v1350(_v429 _v583);
bkr_i64 _v1345(_v433 _v473);
bkr_i64 _v1351(_v434 _v608);
_v338 _v1352(bkr_i64 _v1261);
_v338 _v1353(_v1249 _v1261);
_v338 _v1354(_v1249 _v1261, bkr_i64 _v1036);
bkr_bool _v1355(_v1249 _v1261);
bkr_bool _v1356(_v1249 _v1261);
bkr_i64 _v1357(bkr_i64 _v1261);
bkr_i64 _v1358(_v1249 _v1261);
bkr_i64 _v1359(bkr_i64 _v1261);
bkr_i64 _v1360(_v1249 _v1261);
bkr_i64 _v1361(_v1249 _v1261);
bkr_bool _v1362(_v1249 _v1261, bkr_str _v1363);
_v1249 _v1364(_v1249 _v1261);
bkr_i64 _v1366(_v1249 _v1261);
_v346 _v1367(_v1249 _v1261);
bkr_i64 _v1388(_v1249 _v1261);
_v433 _v1389(_v1249 _v1261);
bkr_i64 _v1410(_v1249 _v1261);
_v426 _v1411(_v1249 _v1261);
bkr_i64 _v1416(_v1249 _v1261);
_v426 _v1417(_v1249 _v1261);
bkr_bool _v1441(_v1249 _v1261);
bkr_i64 _v1442(_v1249 _v1261);
_v426 _v1443(_v1249 _v1261);
bkr_i64 _v1466(_v1249 _v1261);
_v426 _v1467(_v1249 _v1261);
bkr_i64 _v1469(_v1249 _v1261);
_v426 _v1470(_v1249 _v1261);
bkr_i64 _v1471(_v1249 _v1261);
_v426 _v1472(_v1249 _v1261);
bkr_i64 _v1473(_v1249 _v1261);
_v426 _v1474(_v1249 _v1261);
bkr_i64 _v1475(_v1249 _v1261);
_v426 _v1476(_v1249 _v1261);
bkr_i64 _v1477(_v1249 _v1261);
_v426 _v1478(_v1249 _v1261);
bkr_i64 _v1479(_v1249 _v1261);
_v426 _v1480(_v1249 _v1261);
bkr_i64 _v1481(_v1249 _v1261);
_v426 _v1482(_v1249 _v1261);
bkr_i64 _v1483(_v1249 _v1261);
_v426 _v1484(_v1249 _v1261);
bkr_i64 _v1485(_v1249 _v1261);
_v426 _v1486(_v1249 _v1261);
bkr_i64 _v1488(_v1249 _v1261);
_v426 _v1412(_v1249 _v1261);
bkr_i64 _v1489(_v1249 _v1261);
_v427 _v1490(_v1249 _v1261);
bkr_i64 _v1493(_v1249 _v1261);
_v427 _v1494(_v1249 _v1261);
bkr_i64 _v1496(_v1249 _v1261);
_v427 _v1497(_v1249 _v1261);
bkr_i64 _v1505(_v1249 _v1261);
_v427 _v1506(_v1249 _v1261);
bkr_i64 _v1509(_v1249 _v1261);
_v427 _v1510(_v1249 _v1261);
bkr_i64 _v1512(_v1249 _v1261);
_v429 _v1415(_v1249 _v1261);
bkr_i64 _v1516(_v1249 _v1261);
_v434 _v1517(_v1249 _v1261);
_v434 _v1518(_v1249 _v1261, bkr_i64 _v1519);
bkr_i64 _v1528(_v1249 _v1261);
_v428 _v1529(_v1249 _v1261);
bkr_i64 _v1531(_v1249 _v1261);
_v428 _v1532(_v1249 _v1261);
bkr_i64 _v1534(_v1249 _v1261);
_v428 _v1535(_v1249 _v1261);
bkr_i64 _v1536(_v1249 _v1261);
_v428 _v1537(_v1249 _v1261);
bkr_i64 _v1540(bkr_i64 _v1261);
bkr_i64 _v1542(_v1249 _v1261);
_v428 _v1543(_v1249 _v1261);
bkr_i64 _v1541(_v1249 _v1261);
bkr_i64 _v1548(bkr_str _v1549, bkr_i64 _v425);
_v1547 _v1551(bkr_str _v1549, bkr_i64 _v425);
_v1547 _v1565(_v1547 _v1566, bkr_i64 _v1567);
bkr_i64 _v1568(_v1547 _v1566);
_v1547 _v1564(bkr_i64 _v1254);
bkr_i64 _v1550(_v1547 _v1566);
bkr_i64 _v1569(bkr_i64 _v1254);
bkr_i64 _v1570(_v1547 _v1566);
bkr_i64 _v1571(bkr_i64 _v1254);
bkr_i64 _v1572(_v1547 _v1566);
bkr_i64 _v1573(bkr_i64 _v1254, bkr_i64 _v1574);
_v1547 _v1575(_v1547 _v1566, bkr_i64 _v1574);
bkr_i64 _v1576(bkr_i64 _v1254);
bkr_i64 _v1577(_v1547 _v1566);
bkr_i64 _v1578(_v1547 _v1566, bkr_str _v1305);
bkr_i64 _v1579(bkr_i64 _v1254);
bkr_i64 _v1580(_v1547 _v1566);
bkr_i64 _v1581(bkr_i64 _v1254);
bkr_i64 _v1582(_v1547 _v1566);
bkr_i64 _v1583(bkr_i64 _v1254);
bkr_i64 _v1584(_v1547 _v1566);
bkr_i64 _v1585(bkr_i64 _v1254);
bkr_i64 _v1586(_v1547 _v1566);
bkr_i64 _v1587(bkr_i64 _v1254);
bkr_i64 _v1588(_v1547 _v1566);
bkr_i64 _v1589(bkr_i64 _v1254);
bkr_i64 _v1590(_v1547 _v1566);
bkr_i64 _v1591(bkr_i64 _v1254);
bkr_i64 _v1592(_v1547 _v1566);
bkr_i64 _v1593(bkr_i64 _v1254);
bkr_i64 _v1594(_v1547 _v1566);
bkr_i64 _v1595(bkr_i64 _v1254);
bkr_i64 _v1596(_v1547 _v1566);
bkr_i64 _v1597(bkr_i64 _v1254, bkr_str _v1598);
_v1547 _v1599(_v1547 _v1566, bkr_str _v1598);
bkr_i64 _v1601(bkr_i64 _v1254);
_v1547 _v1602(_v1547 _v1566);
bkr_i64 _v1603(bkr_i64 _v1254);
_v1547 _v1604(_v1547 _v1566);
bkr_i64 _v1605(bkr_i64 _v1254);
_v1547 _v1606(_v1547 _v1566);
bkr_i64 _v1607(bkr_i64 _v1254, bkr_i64 _v355, bkr_i64 _v319);
_v1547 _v1608(_v1547 _v1566, bkr_i64 _v355, bkr_i64 _v319);
_v1547 _v1610(_v1547 _v1566, bkr_i64 _v355, bkr_i64 _v319, bkr_i64 _v1519);
bkr_i64 _v1609(_v1547 _v1566);
bkr_i64 _v1612(_v1547 _v1566, bkr_i64 _v355);
bkr_i64 _v1613(_v1547 _v1566);
_v1547 _v1614(_v1547 _v1566, bkr_i64 _v1615);
bkr_str _v1616(_v1547 _v1566);
_v1547 _v1617(_v1547 _v1566, bkr_str _v1146);
bkr_i64 _v1618(_v1547 _v1566);
bkr_str _v1620(_v1547 _v1566, bkr_str _v1600);
bkr_i64 _v1622(bkr_i64 _v1254, bkr_i64 _v355, bkr_i64 _v319);
_v1547 _v1623(_v1547 _v1566, bkr_i64 _v355, bkr_i64 _v319);
bkr_i64 _v1624(bkr_i64 _v1254, bkr_i64 _v355, bkr_i64 _v319);
_v1547 _v1625(_v1547 _v1566, bkr_i64 _v355, bkr_i64 _v319);
bkr_i64 _v1626(bkr_i64 _v1254, bkr_i64 _v355, bkr_i64 _v954, bkr_i64 _v955);
_v1547 _v1627(_v1547 _v1566, bkr_i64 _v355, bkr_i64 _v954, bkr_i64 _v955);
bkr_i64 _v1628(bkr_i64 _v1254, bkr_i64 _v355);
bkr_i64 _v1629(_v1547 _v1566, bkr_i64 _v355);
bkr_i64 _v1630(bkr_i64 _v1254, bkr_i64 _v355);
bkr_i64 _v1631(_v1547 _v1566, bkr_i64 _v355);
bkr_i64 _v1632(bkr_i64 _v425, bkr_i64 _v1633, bkr_i64 _v355);
bkr_i64 _v1634(bkr_i64 _v1254, bkr_i64 _v355);
bkr_i64 _v1635(_v1547 _v1566, bkr_i64 _v355);
bkr_i64 _v1637(bkr_i64 _v1254, bkr_i64 _v355);
bkr_i64 _v1638(_v1547 _v1566, bkr_i64 _v355);
bkr_bool _v1639(_v1547 _v1254, bkr_i64 _v355);
bkr_bool _v1640(_v1547 _v1254, bkr_str _v1642);
bkr_i64 _v1643(_v1547 _v1254, bkr_str _v1642, bkr_str _v1644);
bkr_i64 _v1646(_v1547 _v1254, bkr_str _v1642, bkr_str _v1644, bkr_i64 _v1647);
bkr_bool _v1649(_v1547 _v1254, bkr_str _v1642);
bkr_str _v1650(bkr_i64 _v319);
bkr_str _v1651(bkr_i64 _v1254, bkr_i64 _v516);
bkr_str _v1652(_v1547 _v1254, _v346 _v521);
bkr_str _v1654(bkr_i64 _v349);
bkr_str _v1641(bkr_i64 _v425, bkr_i64 _v1036);
bkr_str _v1655(bkr_str _v1656);
bkr_str _v1657(bkr_i64 _v425, bkr_i64 _v1036);
bkr_str _v1660(bkr_i64 _v1254, bkr_i64 _v1036);
bkr_str _v1653(_v1547 _v1254, bkr_i64 _v1036);
bkr_i64 _v1661(bkr_i64 _v516);
bkr_i64 _v1662(_v346 _v521);
bkr_i64 _v1663(bkr_i64 _v516);
bkr_i64 _v1664(_v346 _v521);
bkr_i64 _v1665(bkr_i64 _v516);
bkr_i64 _v1666(_v346 _v521);
bkr_i64 _v1667(bkr_str _v1656);
bkr_i64 _v1668(bkr_i64 _v1254, bkr_i64 _v368);
bkr_i64 _v1670(bkr_i64 _v1254, bkr_i64 _v1671);
bkr_i64 _v1672(_v1547 _v1254, bkr_i64 _v1671);
_v346 _v1673(_v1547 _v1254, bkr_i64 _v1519, bkr_i64 _v1674);
bkr_i64 _v1675(_v1547 _v1254, bkr_i64 _v1519, bkr_i64 _v1647);
bkr_bool _v1676(_v1547 _v1254, bkr_i64 _v1519);
bkr_bool _v1677(_v1547 _v1254, bkr_i64 _v1519);
bkr_str _v1680(_v1547 _v1254, bkr_i64 _v1519, bkr_str _v1681);
_v346 _v1684(_v1547 _v1254, bkr_i64 _v1545);
bkr_i64 _v1669(_v1547 _v1254, _v426 _v542);
bkr_str _v1705(bkr_i64 _v1254, bkr_i64 _v370);
bkr_str _v1706(_v1547 _v1254, _v427 _v554);
bkr_str _v1718(bkr_i64 _v1254, bkr_str _v1719, bkr_i64 _v379);
bkr_str _v1720(_v1547 _v1254, bkr_str _v1719, _v341 _v1127);
bkr_str _v1724(bkr_i64 _v1254, bkr_str _v1725, bkr_i64 _v463);
bkr_str _v1726(_v1547 _v1254, bkr_str _v1725, _v433 _v473);
bkr_str _v1730(bkr_i64 _v1254, bkr_str _v1725, bkr_i64 _v463, bkr_i64 _v1731);
bkr_str _v1732(_v1547 _v1254, bkr_str _v1725, _v433 _v473, bkr_i64 _v1731);
bkr_str _v1751(bkr_i64 _v1254, bkr_i64 _v368);
bkr_str _v1752(_v1547 _v1254, _v426 _v542);
bkr_bool _v1759(bkr_i64 _v1254, bkr_i64 _v368);
bkr_bool _v1760(_v1547 _v1254, _v426 _v542);
bkr_str _v1761(bkr_i64 _v1254, bkr_i64 _v368);
bkr_str _v1762(_v1547 _v1254, _v426 _v542);
bkr_str _v1763(bkr_i64 _v1254, bkr_i64 _v516, bkr_i64 _v366);
bkr_str _v1717(_v1547 _v1254, bkr_i64 _v516, _v426 _v1709);
bkr_str _v1765(bkr_i64 _v1254, bkr_i64 _v368);
bkr_str _v1708(_v1547 _v1254, _v426 _v542);
bkr_i64 _v1847(bkr_i64 _v1254, bkr_i64 _v370);
_v1547 _v1801(_v1547 _v1254, _v427 _v554);
bkr_str _v1766(bkr_str _v1656);
bkr_i64 _v1861(bkr_i64 _v1254, bkr_i64 _v578);
_v1547 _v1852(_v1547 _v1254, _v429 _v583);
bkr_str _v1862(bkr_i64 _v1254, bkr_i64 _v930);
bkr_str _v1863(_v1547 _v1254, _v428 _v1530);
bkr_i64 _v1868(bkr_i64 _v1254, bkr_i64 _v930);
_v1547 _v1869(_v1547 _v1254, _v428 _v1530);
bkr_i64 _v1870(bkr_i64 _v1254, bkr_i64 _v930);
_v1547 _v1871(_v1547 _v1254, _v428 _v1530);
bkr_i64 _v1876(bkr_i64 _v1254, bkr_i64 _v1877);
_v1547 _v1878(_v1547 _v1254, _v428 _v1533);
bkr_i64 _v1881(bkr_i64 _v1254, bkr_i64 _v933);
_v1547 _v1882(_v1547 _v1254, _v428 _v1539);
bkr_i64 _v1884(bkr_i64 _v1254, bkr_i64 _v0);
_v1547 _v1885(_v1547 _v1254, _v341 _v1546);
bkr_i64 _v1886(bkr_i64 _v1254, bkr_i64 _v0);
_v1547 _v1887(_v1547 _v1254, _v341 _v1546);
bkr_i64 _v1888(bkr_i64 _v1254, bkr_i64 _v0);
_v1547 _v1889(_v1547 _v1254, _v341 _v1546);
_v1547 _v1890(_v1547 _v1254, _v341 _v1546);
bkr_i64 _v1893(bkr_i64 _v1254, bkr_i64 _v0);
_v1547 _v1894(_v1547 _v1254, _v341 _v1546);
bkr_i64 _v1895(bkr_i64 _v1254, bkr_i64 _v0);
_v1547 _v1896(_v1547 _v1254, _v341 _v1546);
bkr_str _v1897(bkr_i64 _v0);
bkr_str _v1898(_v341 _v1546);
bkr_str _v1901(bkr_str _v1656);
bkr_str _v1903(bkr_str _v1398);
bkr_str _v1904(bkr_i64 _v1398);
bkr_str _v1905(bkr_bool _v1398);
bkr_str _v1906(void);
bkr_str _v1907(bkr_str _v1841, bkr_str _v1398);
bkr_str _v1908(bkr_str _v1841, bkr_i64 _v1398);
bkr_str _v1909(bkr_str _v1841, bkr_bool _v1398);
bkr_str _v1910(bkr_str _v1841, bkr_str _v1911);
_v1912 _v1914(void);
void _v1916(_v1912 _v1917, bkr_str _v1841, bkr_str _v1398);
void _v1918(_v1912 _v1917, bkr_str _v1841, bkr_i64 _v1398);
void _v1919(_v1912 _v1917, bkr_str _v1841, bkr_bool _v1398);
void _v1920(_v1912 _v1917, bkr_str _v1841, bkr_str _v1911);
bkr_str _v1921(_v1912 _v1917);
_v1922 _v1923(void);
void _v1925(_v1922 _v1926, bkr_str _v1398);
void _v1927(_v1922 _v1926, bkr_i64 _v1398);
void _v1928(_v1922 _v1926, bkr_bool _v1398);
void _v1929(_v1922 _v1926, bkr_str _v1911);
bkr_str _v1930(_v1922 _v1926);
bkr_i64 _v1931(bkr_str _v1932, bkr_i64 _v1933);
bkr_str _v1934(bkr_str _v1932, bkr_str _v1841);
bkr_str _v1940(bkr_str _v1932, bkr_str _v1841);
bkr_i64 _v1941(bkr_str _v1932, bkr_str _v1841);
bkr_bool _v1942(bkr_str _v1932, bkr_str _v1841);
bkr_bool _v1943(bkr_str _v1932, bkr_str _v1841);
bkr_i64 _v1944(bkr_str _v1945);
bkr_bool _v1947(_v341 _v1546);
bkr_str _v1948(bkr_str _v1656);
bkr_str _v1949(bkr_str _v319, bkr_i64 _v1950, bkr_i64 _v1951, bkr_str _v1952, bkr_str _v1953, bkr_str _v1954);
bkr_str _v1956(void);
bkr_str _v1957(bkr_str _v1958);
bkr_str _v1959(bkr_i64 _v425, bkr_i64 _v1036);
bkr_i64 _v1960(void);
bkr_str _v1961(bkr_i64 _v1254);
bkr_i64 _v1963(bkr_i64 _v1254);
bkr_i64 _v1964(bkr_i64 _v1254, bkr_str _v1962);
bkr_bool _v1965(bkr_i64 _v613, bkr_i64 _v387);
bkr_i64 _v1966(void);
bkr_i64 _v1967(bkr_i64 _v613);
bkr_i64 _v1969(bkr_i64 _v613, bkr_i64 _v387);
bkr_i64 _v1970(bkr_str _v1212);
bkr_i64 _v1971(bkr_i64 _v558);
bkr_i64 _v1972(_v428 _v563);
bkr_i64 _v1973(bkr_i64 _v558);
bkr_i64 _v1974(_v428 _v563);
bkr_i64 _v1975(bkr_i64 _v558);
bkr_i64 _v1976(_v428 _v563);
bkr_i64 _v1977(bkr_i64 _v558);
bkr_i64 _v1978(_v428 _v563);
bkr_str _v1979(bkr_i64 _v425, bkr_i64 _v558);
bkr_str _v1980(bkr_i64 _v425, _v428 _v563);
bkr_i64 _v1982(bkr_i64 _v423, bkr_i64 _v319);
bkr_i64 _v1983(_v434 _v1186, bkr_i64 _v319);
bkr_str _v1984(bkr_i64 _v0);
bkr_str _v1985(bkr_i64 _v425, _v434 _v1186);
bkr_str _v1986(bkr_i64 _v425, bkr_i64 _v606);
bkr_str _v1987(bkr_i64 _v425, _v434 _v608);
bkr_str _v1989(bkr_i64 _v425, bkr_i64 _v1990);
bkr_str _v1991(bkr_i64 _v425, bkr_i64 _v578);
bkr_str _v1992(bkr_i64 _v425, _v429 _v583);
bkr_str _v1993(bkr_i64 _v425, bkr_i64 _v463);
bkr_str _v1994(bkr_i64 _v425, _v433 _v473);
bkr_str _v1995(bkr_i64 _v425, bkr_i64 _v406, bkr_i64 _v407);
bkr_str _v1996(bkr_i64 _v425, _v436 _v621, _v434 _v976);
bkr_str _v1997(bkr_i64 _v425, bkr_i64 _v447);
bkr_str _v1998(bkr_i64 _v425, _v426 _v542);
bkr_str _v1999(bkr_i64 _v425, bkr_i64 _v2000);
bkr_str _v2001(bkr_i64 _v425, bkr_i64 _v1615);
bkr_str _v2002(bkr_i64 _v425, bkr_i64 _v447);
bkr_str _v1988(bkr_i64 _v425, _v341 _v452);
bkr_str _v2004(bkr_str _v1212, bkr_i64 _v0);
bkr_str _v2010(bkr_str _v1212, bkr_i64 _v0);
bkr_str _v2011(bkr_str _v1196, bkr_str _v558);
bkr_str _v2012(bkr_str _v1196, bkr_str _v423);
bkr_str _v2014(bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v1950, bkr_i64 _v1951);
bkr_str _v2016(bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v341 _v452);
bkr_str _v2017(bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447);
bkr_str _v2018(bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v433 _v473);
bkr_str _v2019(bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v463);
bkr_str _v2020(bkr_i64 _v425, bkr_i64 _v516, bkr_str _v2015);
bkr_str _v2021(bkr_i64 _v425, _v346 _v521, bkr_str _v2015);
bkr_str _v2022(bkr_i64 _v425, bkr_i64 _v463, bkr_str _v2015);
bkr_str _v2023(bkr_i64 _v425, _v433 _v473, bkr_str _v2015);
bkr_str _v2027(bkr_i64 _v425, bkr_i64 _v1671, bkr_str _v2015);
bkr_str _v2028(bkr_i64 _v425, _v426 _v542, bkr_str _v2015);
bkr_str _v2031(bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2015);
bkr_str _v2032(bkr_i64 _v425, _v427 _v554, bkr_str _v2015);
bkr_str _v2033(bkr_i64 _v425, bkr_i64 _v578, bkr_str _v2015);
bkr_str _v2029(bkr_i64 _v425, _v429 _v583, bkr_str _v2015);
bkr_str _v2034(bkr_i64 _v0, bkr_i64 _v558, bkr_str _v2035);
bkr_str _v2036(_v341 _v1546, _v428 _v563, bkr_str _v2035);
bkr_str _v2040(bkr_i64 _v0);
bkr_str _v2041(_v341 _v1546);
bkr_str _v2042(bkr_i64 _v425, bkr_i64 _v1671, bkr_str _v2015);
bkr_str _v2043(bkr_i64 _v425, _v426 _v542, bkr_str _v2015);
bkr_str _v2045(bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2015);
bkr_str _v2046(bkr_i64 _v425, _v427 _v554, bkr_str _v2015);
bkr_str _v2047(bkr_i64 _v425, bkr_i64 _v578, bkr_str _v2015);
bkr_str _v2044(bkr_i64 _v425, _v429 _v583, bkr_str _v2015);
bkr_str _v2048(bkr_i64 _v0, bkr_i64 _v558, bkr_str _v2035);
bkr_str _v2049(_v341 _v1546, _v428 _v563, bkr_str _v2035);
bkr_str _v2050(bkr_i64 _v0);
bkr_str _v2051(_v341 _v1546);
bkr_str _v2052(bkr_i64 _v0);
bkr_str _v2055(bkr_i64 _v0);
bkr_str _v2056(bkr_i64 _v319, bkr_str _v1212);
bkr_str _v2057(bkr_i64 _v425, bkr_i64 _v516, bkr_str _v1212);
bkr_str _v2058(bkr_i64 _v425, _v346 _v521, bkr_str _v1212);
bkr_str _v2059(bkr_i64 _v1254, bkr_i64 _v1671);
bkr_str _v2060(_v1547 _v1254, bkr_i64 _v1671);
bkr_str _v2061(_v1547 _v1254, _v426 _v542);
bkr_i64 _v2062(bkr_i64 _v1254, bkr_i64 _v516, bkr_i64 _v1671);
bkr_i64 _v2063(_v1547 _v1254, bkr_i64 _v516, bkr_i64 _v1671);
bkr_i64 _v2065(bkr_i64 _v1254, bkr_i64 _v355, bkr_i64 _v516);
_v1547 _v2066(_v1547 _v1254, bkr_i64 _v355, _v346 _v521);
bkr_i64 _v2067(bkr_i64 _v0);
_v1547 _v2068(_v341 _v1546);
bkr_str _v2070(bkr_str _v1196, bkr_str _v558);
bkr_str _v2071(bkr_str _v1196, bkr_str _v423);
bkr_str _v2072(bkr_i64 _v425, bkr_i64 _v1139);
bkr_str _v2073(bkr_i64 _v425, _v341 _v1523);
bkr_str _v2074(bkr_i64 _v425, bkr_i64 _v411);
bkr_str _v2075(bkr_i64 _v425, _v434 _v1145);
bkr_str _v2076(bkr_i64 _v425, bkr_i64 _v1154);
bkr_str _v2077(bkr_i64 _v425, _v341 _v1447);
bkr_str _v2078(bkr_i64 _v425, bkr_i64 _v416);
bkr_str _v2079(bkr_i64 _v425, _v434 _v1162);
bkr_str _v2080(bkr_i64 _v425, bkr_i64 _v558);
bkr_str _v2081(bkr_i64 _v425, _v428 _v563);
bkr_str _v2082(bkr_i64 _v0);
bkr_str _v2083(_v341 _v1546);
bkr_str _v2084(bkr_i64 _v1254, bkr_i64 _v425, bkr_i64 _v558);
bkr_str _v2085(_v1547 _v1254, bkr_i64 _v425, _v428 _v563);
bkr_str _v2086(bkr_i64 _v0, bkr_i64 _v1254);
bkr_str _v2087(_v341 _v1546, _v1547 _v1254);
bkr_str _v2088(bkr_i64 _v1254, bkr_i64 _v425, bkr_i64 _v370);
bkr_str _v2089(_v1547 _v1254, bkr_i64 _v425, _v427 _v554);
bkr_i64 _v2092(bkr_i64 _v1254, bkr_i64 _v370);
_v1547 _v2093(_v1547 _v1254, _v427 _v554);
bkr_str _v2094(bkr_i64 _v1254, bkr_i64 _v425, bkr_i64 _v578);
bkr_str _v2095(_v1547 _v1254, bkr_i64 _v425, _v429 _v583);
bkr_str _v2096(bkr_i64 _v1254, bkr_i64 _v370);
bkr_str _v2097(_v1547 _v1254, _v427 _v554);
bkr_str _v2098(bkr_i64 _v1254, bkr_i64 _v425, bkr_i64 _v578);
bkr_str _v2099(_v1547 _v1254, bkr_i64 _v425, _v429 _v583);
bkr_i64 _v2100(bkr_i64 _v0, bkr_i64 _v930);
_v1547 _v2101(_v341 _v1546, _v428 _v1530);
bkr_str _v2105(bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v558);
bkr_str _v2106(_v341 _v1546, bkr_i64 _v425, _v428 _v563);
bkr_str _v2109(bkr_i64 _v0);
bkr_str _v2110(_v341 _v1546);
bkr_str _v2111(bkr_i64 _v0);
bkr_str _v2115(bkr_i64 _v0);
bkr_str _v2116(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v1950, bkr_i64 _v1951, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117);
bkr_str _v2118(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v1950, bkr_i64 _v1951, bkr_str _v1279, bkr_str _v1282, bkr_str _v2119, bkr_str _v2117);
bkr_str _v2120(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117);
bkr_str _v2121(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117);
bkr_str _v2122(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_str _v1279, bkr_str _v1282, bkr_str _v2119, bkr_str _v2117);
bkr_str _v2123(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v463, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117);
bkr_str _v2124(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, _v433 _v473, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117);
bkr_i64 _v2125(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_str _v2126, bkr_i64 _v447);
bkr_i64 _v2127(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_str _v2126, _v341 _v452);
bkr_i64 _v2129(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v463);
bkr_i64 _v2130(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v433 _v473);
bkr_i64 _v2131(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_str _v2132, bkr_i64 _v447, bkr_str _v1279);
bkr_i64 _v2133(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_str _v2132, _v341 _v452, bkr_str _v1279);
bkr_i64 _v2134(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_str _v2132, _v341 _v452, bkr_str _v1279, bkr_str _v2119);
bkr_str _v2135(bkr_str _v1196, bkr_str _v558);
bkr_str _v2136(bkr_str _v319, bkr_str _v1363, _v341 _v452);
bkr_str _v2137(_v341 _v1546, bkr_i64 _v425);
bkr_str _v2138(_v341 _v1546, bkr_i64 _v425);
bkr_str _v2139(_v341 _v1546, bkr_i64 _v425);
bkr_str _v2140(_v341 _v1546, bkr_i64 _v425, bkr_i64 _v1519);
bkr_bool _v2141(bkr_str _v1363);
bkr_bool _v2142(bkr_i64 _v0, bkr_i64 _v355);
bkr_bool _v2143(_v341 _v1546, bkr_i64 _v355);
bkr_bool _v2144(bkr_i64 _v0, bkr_i64 _v355);
bkr_bool _v2145(_v341 _v1546, bkr_i64 _v355);
bkr_bool _v2146(bkr_i64 _v0, bkr_i64 _v355);
bkr_bool _v2148(_v341 _v1546, bkr_i64 _v355);
bkr_bool _v2147(_v341 _v1546, bkr_i64 _v355);
bkr_bool _v2149(_v341 _v1546, bkr_i64 _v355);
bkr_bool _v2150(bkr_i64 _v0, bkr_i64 _v1519, bkr_i64 _v1674);
bkr_bool _v2151(_v341 _v1546, bkr_i64 _v1519, bkr_i64 _v1674);
bkr_i64 _v2152(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v516, bkr_str _v2015);
bkr_i64 _v2153(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, bkr_i64 _v516, bkr_str _v2015);
bkr_i64 _v2154(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v346 _v521, bkr_str _v2015);
bkr_i64 _v2155(bkr_i64 _v1254, bkr_i64 _v425, bkr_i64 _v463, bkr_str _v2015, bkr_i64 _v2156);
bkr_i64 _v2157(bkr_i64 _v1254, bkr_i64 _v425, _v433 _v473, bkr_str _v2015, bkr_i64 _v2156);
bkr_i64 _v2158(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v1671, bkr_str _v2015, bkr_i64 _v2156);
bkr_i64 _v2159(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, bkr_i64 _v1671, bkr_str _v2015, bkr_i64 _v2156);
bkr_i64 _v2160(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v426 _v542, bkr_str _v2015, bkr_i64 _v2156);
bkr_i64 _v2168(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2015, bkr_i64 _v2156, bkr_i64 _v2169);
bkr_i64 _v2170(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v427 _v554, bkr_str _v2015, bkr_i64 _v2156, bkr_i64 _v2169);
bkr_i64 _v2173(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v578, bkr_str _v2015, bkr_i64 _v2174, bkr_i64 _v2175);
bkr_i64 _v2163(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v429 _v583, bkr_str _v2015, bkr_i64 _v2174, bkr_i64 _v2175);
bkr_i64 _v2176(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v558, bkr_str _v2035);
bkr_i64 _v2177(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v428 _v563, bkr_str _v2035);
bkr_i64 _v2178(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v558);
bkr_i64 _v2179(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v428 _v563);
bkr_i64 _v2180(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425);
bkr_i64 _v2181(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425);
bkr_i64 _v2182(bkr_i64 _v1254, bkr_i64 _v0);
bkr_i64 _v2183(bkr_i64 _v1254, _v341 _v1546);
bkr_str _v2184(bkr_i64 _v0);
bkr_str _v2185(bkr_i64 _v0);
bkr_bool _v2186(bkr_i64 _v319);
bkr_bool _v2187(bkr_i64 _v319);
bkr_bool _v2188(bkr_i64 _v319);
bkr_bool _v2189(bkr_i64 _v2190, bkr_i64 _v2191);
bkr_bool _v2192(bkr_i64 _v319);
bkr_bool _v2193(bkr_i64 _v319);
bkr_bool _v2194(bkr_i64 _v2195, bkr_i64 _v1803);
bkr_bool _v2200(bkr_i64 _v2190, bkr_i64 _v2191);
bkr_i64 _v2201(_v1547 _v2202, bkr_i64 _v1671);
bkr_i64 _v2203(_v1547 _v2202, _v426 _v542);
bkr_i64 _v2204(bkr_i64 _v516);
bkr_i64 _v2206(_v341 _v1546, bkr_i64 _v355);
bkr_bool _v2207(_v341 _v1546, bkr_i64 _v355);
bkr_i64 _v2064(_v341 _v1546, _v346 _v521);
bkr_i64 _v2209(_v341 _v1546, _v428 _v1530);
bkr_i64 _v2205(_v346 _v521);
bkr_i64 _v2210(bkr_i64 _v930);
bkr_i64 _v2211(_v428 _v1530);
bkr_str _v2212(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447, bkr_str _v1279, bkr_str _v2213, bkr_str _v2117);
bkr_str _v2214(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_str _v1279, bkr_str _v2213, bkr_str _v2117);
bkr_str _v2215(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_str _v1279, bkr_str _v2213, bkr_str _v2216, bkr_str _v2217, bkr_str _v2117);
bkr_str _v2218(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v1950, bkr_i64 _v1951, bkr_str _v1279, bkr_str _v2213, bkr_str _v2216, bkr_str _v2217, bkr_str _v2117);
bkr_i64 _v2219(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117);
bkr_i64 _v2220(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117);
bkr_i64 _v2221(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_i64 _v2222, bkr_i64 _v2223, bkr_str _v2117);
bkr_i64 _v2224(bkr_i64 _v1254, bkr_str _v2015, _v426 _v1098);
bkr_i64 _v2225(bkr_i64 _v1254, bkr_str _v2015, _v427 _v554);
bkr_i64 _v2227(bkr_i64 _v1254, bkr_i64 _v425, bkr_str _v2015, _v426 _v1098);
bkr_i64 _v2229(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v426 _v542);
bkr_i64 _v2230(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v426 _v542);
bkr_i64 _v2231(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v426 _v542);
bkr_i64 _v2232(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v426 _v542);
bkr_i64 _v2233(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v426 _v542);
bkr_i64 _v2234(bkr_i64 _v1254, bkr_i64 _v425, _v341 _v1546, bkr_str _v2035);
bkr_i64 _v2235(bkr_i64 _v1254, bkr_i64 _v425, bkr_str _v2035, _v428 _v2236, bkr_str _v1279, bkr_str _v2213, bkr_str _v2117);
bkr_i64 _v2237(bkr_i64 _v1254, bkr_i64 _v425, bkr_str _v2015, _v426 _v542, bkr_str _v1282);
bkr_i64 _v2238(bkr_i64 _v1254, bkr_i64 _v425, bkr_str _v2015, _v428 _v1530);
bkr_i64 _v2239(bkr_i64 _v1254, _v1547 _v2202, _v426 _v542, bkr_str _v1363, bkr_str _v2015);
bkr_i64 _v2240(bkr_i64 _v1254, bkr_str _v2015, _v427 _v554);
bkr_bool _v2241(_v426 _v1098);
bkr_bool _v2242(_v426 _v542);
bkr_bool _v2243(bkr_i64 _v1671);
bkr_bool _v2244(bkr_i64 _v425, _v426 _v542);
bkr_bool _v2245(bkr_i64 _v425, bkr_i64 _v1671);
bkr_bool _v2246(bkr_i64 _v425, _v426 _v542);
bkr_bool _v2247(bkr_i64 _v425, bkr_i64 _v1671);
bkr_bool _v2248(bkr_i64 _v425, _v426 _v542);
bkr_bool _v2249(bkr_i64 _v425, bkr_i64 _v1671);
bkr_bool _v2250(_v1547 _v2202, bkr_i64 _v1671);
bkr_i64 _v2251(bkr_str _v1363);
bkr_i64 _v2252(bkr_str _v1363, bkr_i64 _v362);
bkr_i64 _v2253(bkr_i64 _v1254, bkr_i64 _v425, _v426 _v542, bkr_str _v2015);
bkr_i64 _v2255(bkr_i64 _v1254, bkr_i64 _v425, _v1547 _v2202, _v426 _v542, bkr_str _v2015);
bkr_i64 _v2258(bkr_i64 _v1254, bkr_i64 _v425, _v1547 _v2202, _v426 _v542, bkr_str _v2015);
bkr_bool _v2259(bkr_i64 _v349);
bkr_bool _v2260(bkr_i64 _v349);
bkr_bool _v2261(bkr_i64 _v349);
bkr_i64 _v2262(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117);
bkr_i64 _v2257(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117);
bkr_i64 _v2263(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117);
bkr_i64 _v2264(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117);
_v428 _v2265(_v341 _v1546, bkr_i64 _v355);
bkr_i64 _v2266(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, bkr_str _v2035);
bkr_i64 _v2269(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v426 _v542, bkr_str _v2015);
_v428 _v2271(_v341 _v1546, bkr_i64 _v355);
_v428 _v2270(_v341 _v1546, bkr_i64 _v355);
bkr_i64 _v2273(_v341 _v1546, bkr_i64 _v1519, bkr_i64 _v1674);
bkr_i64 _v2274(bkr_i64 _v1254, bkr_i64 _v425, _v426 _v542, bkr_str _v2015);
bkr_bool _v2275(_v435 _v1008, bkr_i64 _v1674);
bkr_i64 _v2276(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v426 _v542, bkr_str _v2015);
bkr_i64 _v2278(bkr_i64 _v1254, bkr_str _v2015, bkr_str _v2279, _v426 _v1032, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117);
bkr_i64 _v2280(bkr_i64 _v1254, _v1547 _v2202, _v426 _v542, bkr_str _v2015);
bkr_bool _v2282(_v1547 _v2202, _v426 _v542);
bkr_i64 _v2283(bkr_i64 _v1254, _v1547 _v2202, _v426 _v542, bkr_str _v2015);
bkr_i64 _v2285(bkr_i64 _v1254, _v1547 _v2202, _v426 _v542, bkr_str _v2015);
bkr_i64 _v2287(bkr_i64 _v1254, _v1547 _v2202, _v426 _v542, bkr_str _v2015);
bkr_i64 _v2288(_v1547 _v2202, _v341 _v1127);
bkr_i64 _v2289(bkr_i64 _v1254, _v1547 _v2202, _v434 _v976, bkr_str _v2015);
bkr_i64 _v2291(_v433 _v473);
bkr_bool _v2293(bkr_i64 _v1731, bkr_i64 _v2190);
bkr_i64 _v2294(bkr_i64 _v1254, _v436 _v621, bkr_i64 _v1731, bkr_str _v2015);
bkr_bool _v2295(_v433 _v473);
bkr_bool _v2296(_v433 _v473);
bkr_bool _v2297(_v433 _v1051, _v433 _v1052);
bkr_i64 _v2306(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v433 _v473, bkr_str _v1279, bkr_str _v2213, bkr_str _v2117);
bkr_i64 _v2307(bkr_i64 _v1254, _v435 _v977, _v436 _v621, bkr_str _v2015);
bkr_bool _v2312(_v435 _v977, _v436 _v621, bkr_i64 _v387);
bkr_bool _v2314(_v436 _v621);
bkr_bool _v2315(bkr_i64 _v2316);
bkr_bool _v2325(_v435 _v977, _v436 _v621, bkr_i64 _v2292);
bkr_i64 _v2326(bkr_i64 _v1254, _v426 _v542, _v436 _v621, bkr_i64 _v1731, bkr_str _v2015);
bkr_i64 _v2330(bkr_i64 _v1254, _v435 _v977, _v436 _v621, bkr_i64 _v1731, bkr_str _v2015);
bkr_i64 _v2332(bkr_i64 _v1254, _v426 _v542, _v436 _v621, bkr_str _v2015);
bkr_i64 _v2335(bkr_i64 _v1254, _v435 _v977, _v436 _v621, bkr_str _v2015);
bkr_bool _v2336(_v436 _v621);
bkr_bool _v2337(_v435 _v977, _v436 _v621, bkr_i64 _v2292);
bkr_i64 _v2338(bkr_i64 _v1254, _v426 _v542, _v436 _v621, bkr_str _v2015);
bkr_i64 _v2341(bkr_i64 _v1254, _v435 _v977, _v436 _v621, bkr_str _v2015);
bkr_bool _v2344(_v436 _v621);
bkr_i64 _v2345(_v436 _v621);
_v428 _v2346(_v341 _v1546, bkr_i64 _v2347);
bkr_bool _v2348(_v435 _v977, _v436 _v621, bkr_i64 _v2347, bkr_i64 _v1403);
bkr_i64 _v2349(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v426 _v542, _v436 _v621, bkr_str _v2015);
bkr_i64 _v2352(bkr_i64 _v1254, _v426 _v542, _v436 _v621, bkr_i64 _v1731, bkr_str _v2015);
bkr_i64 _v2354(bkr_i64 _v1254, _v341 _v1546, _v435 _v977, _v436 _v621, bkr_str _v2015);
bkr_bool _v2357(_v435 _v1166, bkr_i64 _v1403);
bkr_bool _v2358(_v436 _v621, bkr_i64 _v2347, bkr_i64 _v1403, bkr_i64 _v2359);
bkr_i64 _v2360(bkr_i64 _v1254, _v1547 _v2202, _v434 _v995, bkr_str _v2015);
bkr_i64 _v2363(bkr_i64 _v1254, bkr_i64 _v1671, bkr_str _v2015, bkr_i64 _v2364);
bkr_i64 _v2365(bkr_i64 _v1254, _v426 _v542, bkr_str _v2015, bkr_i64 _v2364);
bkr_i64 _v2367(bkr_i64 _v1254, _v427 _v554, bkr_str _v2015, bkr_i64 _v2364);
bkr_i64 _v2366(bkr_i64 _v1254, _v429 _v583, bkr_str _v2015, bkr_i64 _v2364);
bkr_bool _v2368(_v427 _v554);
bkr_bool _v2369(_v429 _v583);
bkr_bool _v2370(_v427 _v554);
bkr_bool _v2371(_v429 _v583);
bkr_i64 _v2372(bkr_i64 _v1254, _v427 _v554, bkr_str _v2015);
bkr_i64 _v2373(bkr_i64 _v1254, _v429 _v583, bkr_str _v2015);
bkr_i64 _v2375(bkr_i64 _v1254, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v1671, bkr_str _v2015, bkr_str _v2376, bkr_str _v1363, bkr_i64 _v2190, bkr_str _v2117);
bkr_i64 _v2378(bkr_i64 _v1254, bkr_i64 _v425, _v1547 _v2202, _v426 _v542, bkr_str _v2015, bkr_str _v2376, bkr_str _v1363, bkr_i64 _v2190, bkr_str _v2117);
bkr_i64 _v2379(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v368, bkr_str _v2015);
bkr_i64 _v2380(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, _v426 _v542, bkr_str _v2015);
bkr_i64 _v2383(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v1671, bkr_str _v2015, bkr_i64 _v2384);
bkr_i64 _v2385(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v1671, bkr_str _v2015, bkr_i64 _v2384);
bkr_i64 _v2386(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, _v426 _v542, bkr_str _v2015, bkr_i64 _v2384);
bkr_i64 _v2396(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v370, bkr_str _v2015, bkr_i64 _v2384);
bkr_i64 _v2397(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, _v427 _v554, bkr_str _v2015, bkr_i64 _v2384);
bkr_i64 _v2399(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v578, bkr_str _v2015, bkr_i64 _v2384);
bkr_i64 _v2394(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, _v429 _v583, bkr_str _v2015, bkr_i64 _v2384);
bkr_i64 _v2400(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v558, bkr_str _v2035);
bkr_i64 _v2401(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, _v428 _v563, bkr_str _v2035);
bkr_i64 _v2402(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v558);
bkr_i64 _v2403(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v428 _v563);
bkr_i64 _v2404(bkr_i64 _v1254, bkr_i64 _v0);
bkr_i64 _v2405(bkr_i64 _v1254, _v341 _v1546);
bkr_str _v2406(bkr_i64 _v0);
bkr_str _v2407(bkr_i64 _v0);
bkr_i64 _v2408(bkr_i64 _v1254, _v341 _v1546);
bkr_str _v2409(bkr_i64 _v0);
bkr_str _v2410(bkr_i64 _v0);
bkr_str _v2423(_v2411 _v2424, bkr_i64 _v1036);
bkr_bool _v2425(_v2411 _v2424, bkr_str _v2426, bkr_str _v1363, _v341 _v452, bkr_str _v1279, bkr_str _v2213, bkr_str _v2128);
bkr_str _v2427(bkr_i64 _v319);
bkr_str _v2428(_v2411 _v2424, _v346 _v521);
bkr_str _v2430(_v2411 _v2424, bkr_i64 _v342);
bkr_bool _v2431(bkr_str _v2432);
bkr_bool _v2433(bkr_str _v2432);
bkr_str _v2434(bkr_str _v2432, bkr_i64 _v362);
bkr_str _v2435(bkr_str _v1363);
bkr_i64 _v2436(_v2411 _v2424, bkr_str _v1363);
bkr_bool _v2437(_v2411 _v2424, bkr_str _v1363, bkr_str _v2432, bkr_bool _v2438);
bkr_i64 _v2439(_v2411 _v2424);
bkr_bool _v2440(_v2411 _v2424, bkr_i64 _v2441);
bkr_i64 _v2443(_v2411 _v2424);
bkr_bool _v2445(_v2411 _v2424, bkr_i64 _v2444);
bkr_bool _v2446(_v2411 _v2424, bkr_i64 _v2447);
bkr_str _v2448(_v2411 _v2424, _v426 _v542);
bkr_str _v2452(_v2411 _v2424, _v426 _v542);
bkr_bool _v2455(_v2411 _v2424, _v426 _v542, bkr_str _v1363);
bkr_bool _v2456(_v2411 _v2424, bkr_i64 _v342);
bkr_bool _v2457(_v2411 _v2424, bkr_str _v2458, bkr_i64 _v2459, bkr_str _v2460, bkr_str _v2461);
bkr_bool _v2463(bkr_str _v1363);
bkr_str _v2462(bkr_str _v1244);
bkr_bool _v2464(_v2411 _v2424, _v426 _v542);
bkr_bool _v2469(_v2411 _v2424, bkr_str _v2169, bkr_i64 _v2470);
bkr_bool _v2471(_v2411 _v2424, bkr_i64 _v342, bkr_bool _v2472);
bkr_bool _v2474(_v2411 _v2424, _v434 _v2475);
bkr_bool _v2473(_v2411 _v2424, _v426 _v542, bkr_bool _v2472);
bkr_bool _v2481(_v2411 _v2424, _v433 _v473, _v341 _v452);
bkr_bool _v2484(_v429 _v583);
bkr_bool _v2480(_v2411 _v2424, _v426 _v542, bkr_bool _v2472);
bkr_bool _v2487(_v2411 _v2424, _v433 _v473);
bkr_bool _v2479(_v2411 _v2424, _v429 _v583);
bkr_bool _v2490(_v2411 _v2424, _v427 _v554);
bkr_str _v2492(_v2411 _v2424, bkr_str _v2037, _v341 _v1523);
_v2411 _v2494(bkr_i64 _v425, bkr_str _v1212);
bkr_i64 _v2496(_v341 _v1546, bkr_str _v1212);
bkr_str _v2499(bkr_i64 _v0, bkr_str _v1212);
_v2502 _v2513(bkr_i64 _v2510);
bkr_bool _v2514(_v2502 _v2515, bkr_str _v1363);
bkr_str _v2516(bkr_str _v2517, bkr_str _v1841);
bkr_bool _v2518(_v2502 _v2515, bkr_str _v2517, bkr_str _v1841, bkr_i64 _v1398);
bkr_i64 _v2520(_v2502 _v2515, bkr_str _v2517, bkr_str _v1841);
bkr_bool _v2521(_v2502 _v2515, bkr_str _v2517, bkr_str _v1841, bkr_str _v1398);
bkr_str _v2522(_v2502 _v2515, bkr_str _v2517, bkr_str _v1841);
bkr_bool _v2523(_v2502 _v2515, bkr_str _v386, bkr_str _v1212, bkr_str _v2501, bkr_i64 _v344);
bkr_i64 _v2524(_v2502 _v2515);
bkr_bool _v2526(_v2502 _v2515);
_v2500 _v2527(_v2502 _v2515);
bkr_bool _v2528(_v2502 _v2515);
bkr_bool _v2529(_v2502 _v2515);
bkr_i64 _v2530(_v2502 _v2515);
bkr_str _v2531(_v2502 _v2515);
_v2533 _v2548(bkr_str _v1363);
bkr_i64 _v2562(_v2533 _v2563, bkr_str _v319);
bkr_bool _v2564(_v2533 _v2563, bkr_i64 _v2565, bkr_i64 _v2566);
bkr_bool _v2567(_v2533 _v2563, bkr_i64 _v1621, bkr_str _v2568);
bkr_bool _v2569(_v2533 _v2563, bkr_i64 _v1621, bkr_i64 _v2570, bkr_i64 _v2571);
bkr_bool _v2572(_v2533 _v2563, bkr_i64 _v1621, bkr_str _v1305);
bkr_bool _v2573(_v2533 _v2563, bkr_i64 _v1621, bkr_i64 _v2574);
bkr_bool _v2575(_v2533 _v2563, bkr_i64 _v1621, bkr_i64 _v2576);
bkr_bool _v2577(_v2533 _v2563, bkr_i64 _v1621, bkr_i64 _v2578);
bkr_bool _v2579(_v2533 _v2563, bkr_i64 _v1621, bkr_str _v2517, bkr_str _v1841);
bkr_bool _v2580(_v2533 _v2563, bkr_i64 _v1621, bkr_str _v386, bkr_str _v2501);
bkr_str _v2581(_v2533 _v2563, bkr_i64 _v1621);
bkr_str _v2582(_v2533 _v2563, bkr_i64 _v1621);
bkr_i64 _v2583(_v2533 _v2563, bkr_i64 _v1621);
bkr_i64 _v2584(_v2533 _v2563, bkr_i64 _v1621);
bkr_i64 _v2585(_v2533 _v2563, bkr_i64 _v1621);
bkr_str _v2586(_v2533 _v2563, bkr_i64 _v1621);
bkr_str _v2587(_v2533 _v2563, bkr_i64 _v1621);
bkr_str _v2588(_v2533 _v2563, bkr_i64 _v1621);
bkr_str _v2589(_v2533 _v2563, bkr_i64 _v1621, _v2502 _v2515);
bkr_bool _v2593(_v2533 _v2563, bkr_i64 _v1621, _v2502 _v2515);
bkr_str _v2594(_v2533 _v2563);
_v2595 _v2606(void);
_v2595 _v2608(bkr_i64 _v1208);
_v2595 _v2609(bkr_str _v1363);
_v2595 _v2610(bkr_str _v1363, bkr_i64 _v2611);
bkr_i64 _v2612(_v2595 _v368, bkr_str _v1363);
bkr_bool _v2613(_v2595 _v368, bkr_str _v1363, bkr_i64 _v2611);
_v2595 _v2614(_v2595 _v2615, _v2595 _v2616);
_v2595 _v2620(_v2595 _v2615, _v2595 _v2616);
_v2595 _v2621(_v2595 _v2615, bkr_i64 _v574);
bkr_bool _v2622(_v2595 _v368);
bkr_i64 _v2623(_v2595 _v368, bkr_i64 _v2624);
bkr_str _v2625(_v2595 _v368);
_v2599 _v2627(bkr_str _v2600);
bkr_bool _v2630(_v2599 _v2631, bkr_str _v2432);
bkr_bool _v2632(_v2599 _v2631, bkr_str _v2432);
bkr_bool _v2633(_v2595 _v2634, _v2595 _v2635);
bkr_str _v2637(_v2595 _v2634, _v2595 _v2635, bkr_i64 _v2624);
bkr_str _v2640(_v2599 _v2631);
_v2642 _v2668(bkr_i64 _v425);
bkr_str _v2669(_v2642 _v2424, bkr_i64 _v1036);
bkr_str _v2670(bkr_i64 _v319);
bkr_bool _v2671(_v2642 _v2424, bkr_str _v2501);
bkr_i64 _v2672(_v2642 _v2424);
bkr_bool _v2673(_v2642 _v2424, bkr_i64 _v2674);
bkr_bool _v2675(_v2642 _v2424, bkr_i64 _v2615, bkr_i64 _v2616);
bkr_bool _v2676(_v2642 _v2424, bkr_i64 _v2615, bkr_i64 _v2616, bkr_i64 _v1208);
bkr_bool _v2677(_v2642 _v2424, bkr_i64 _v387);
bkr_bool _v2678(_v2642 _v2424, bkr_i64 _v387);
bkr_bool _v2679(_v2642 _v2424, bkr_i64 _v1213, bkr_i64 _v387);
bkr_bool _v2680(_v2642 _v2424, bkr_i64 _v1213, bkr_i64 _v386);
bkr_bool _v2681(_v2642 _v2424, bkr_i64 _v387);
bkr_bool _v2682(_v2642 _v2424, bkr_i64 _v1289);
bkr_bool _v2683(_v2642 _v2424, bkr_i64 _v1289);
bkr_bool _v2684(_v2642 _v2424, bkr_i64 _v1289);
bkr_bool _v2685(_v2642 _v2424, bkr_i64 _v1289);
bkr_bool _v2686(_v2642 _v2424, bkr_i64 _v1289);
bkr_bool _v2687(_v2642 _v2424, bkr_i64 _v1226);
bkr_bool _v2688(_v2642 _v2424, bkr_i64 _v387);
bkr_bool _v2689(_v2642 _v2424, bkr_i64 _v387);
bkr_bool _v2690(_v2642 _v2424, bkr_i64 _v2691);
bkr_bool _v2692(_v2642 _v2424, bkr_i64 _v387);
bkr_bool _v2693(_v2642 _v2424, bkr_i64 _v2694);
bkr_i64 _v2695(_v2642 _v2424);
bkr_bool _v2696(_v2642 _v2424);
bkr_bool _v2697(_v2642 _v2424);
bkr_bool _v2698(_v2642 _v2424);
bkr_bool _v2699(_v2642 _v2424);
bkr_bool _v2700(_v2642 _v2424, bkr_i64 _v2701);
bkr_i64 _v2702(_v2642 _v2424);
bkr_i64 _v2703(_v2642 _v2424);
bkr_i64 _v2704(_v2642 _v2424);
bkr_bool _v2705(_v2642 _v2424, bkr_i64 _v386);
bkr_bool _v2706(_v2642 _v2424);
bkr_i64 _v2707(_v2642 _v2424, bkr_i64 _v2694);
bkr_i64 _v2708(_v2642 _v2424, bkr_str _v1363, bkr_i64 _v1289, bkr_str _v1679);
bkr_i64 _v2709(_v2642 _v2424, bkr_str _v1363);
bkr_i64 _v2710(_v2642 _v2424, bkr_str _v1363);
bkr_i64 _v2711(_v2642 _v2424, bkr_str _v1363);
bkr_str _v2712(_v2642 _v2424, bkr_str _v1363);
bkr_i64 _v2713(_v2642 _v2424);
bkr_bool _v2714(_v2642 _v2424, bkr_i64 _v2441);
bkr_bool _v2715(_v2642 _v2424, bkr_str _v1679);
bkr_bool _v2716(_v2642 _v2424, bkr_str _v1679);
bkr_str _v2717(bkr_i64 _v319);
bkr_str _v2718(bkr_str _v1679, bkr_str _v1600, bkr_i64 _v362);
bkr_bool _v2719(_v2642 _v2424, bkr_str _v1679);
bkr_i64 _v2720(_v2642 _v2424, bkr_str _v1679);
bkr_str _v2721(_v2642 _v2424, bkr_str _v1679);
bkr_i64 _v2722(_v2642 _v2424, bkr_str _v1679);
bkr_str _v2723(_v2642 _v2424, _v346 _v521);
bkr_str _v2724(bkr_str _v1363);
bkr_str _v2725(_v2642 _v2424, bkr_i64 _v342);
bkr_i64 _v2726(_v2642 _v2424, bkr_str _v1697, bkr_str _v1154);
bkr_i64 _v2727(_v2642 _v2424, bkr_str _v1697, bkr_i64 _v2728);
bkr_i64 _v2730(_v2642 _v2424, bkr_str _v1363, bkr_i64 _v1365);
bkr_str _v2733(_v2642 _v2424, _v426 _v542);
bkr_str _v2736(_v2642 _v2424, bkr_str _v1363);
bkr_str _v2735(_v2642 _v2424, _v426 _v542);
bkr_bool _v2743(_v2642 _v2424, bkr_i64 _v342);
bkr_bool _v2744(_v2642 _v2424, _v426 _v542);
bkr_bool _v2745(_v2642 _v2424, _v426 _v542);
bkr_bool _v2756(_v2642 _v2424, _v426 _v542);
bkr_bool _v2748(_v2642 _v2424, _v426 _v542);
bkr_bool _v2750(_v2642 _v2424, bkr_str _v2768, bkr_i64 _v2749);
bkr_bool _v2775(_v2642 _v2424, bkr_i64 _v2776, bkr_i64 _v1289);
bkr_bool _v2764(_v2642 _v2424, bkr_str _v1363, _v434 _v1016);
bkr_bool _v2777(_v2642 _v2424, bkr_i64 _v2776);
bkr_bool _v2766(_v2642 _v2424, bkr_i64 _v361, bkr_i64 _v2498, bkr_i64 _v2459);
bkr_bool _v2751(_v2642 _v2424, _v426 _v542);
bkr_bool _v2758(_v2642 _v2424, _v429 _v583);
bkr_bool _v2781(_v2642 _v2424, bkr_i64 _v342);
bkr_i64 _v2782(_v2642 _v2424, _v433 _v473);
bkr_i64 _v2783(_v2642 _v2424, bkr_i64 _v2753, bkr_i64 _v2691, bkr_i64 _v2784);
bkr_bool _v2786(_v2642 _v2424, _v433 _v473, bkr_i64 _v2753, bkr_i64 _v2787);
bkr_i64 _v2788(_v2642 _v2424, bkr_i64 _v2753);
bkr_bool _v2789(_v2642 _v2424, bkr_i64 _v355, bkr_i64 _v2753, bkr_i64 _v2691, bkr_i64 _v2784, bkr_str _v1679);
bkr_bool _v2790(_v2642 _v2424, _v433 _v473, bkr_i64 _v2753, bkr_str _v1679);
bkr_bool _v2757(_v2642 _v2424, _v426 _v542);
bkr_bool _v2795(_v2642 _v2424, _v429 _v583);
bkr_bool _v2796(_v2642 _v2424, bkr_i64 _v342, bkr_str _v1363);
bkr_i64 _v2797(_v2642 _v2424);
bkr_bool _v2798(_v2642 _v2424, bkr_i64 _v2799, bkr_i64 _v2800, bkr_i64 _v1621, bkr_i64 _v386);
bkr_bool _v2801(_v2642 _v2424, bkr_i64 _v1621, bkr_i64 _v2802, bkr_i64 _v2803);
bkr_i64 _v2804(_v2642 _v2424);
bkr_bool _v2780(_v2642 _v2424, _v427 _v554);
bkr_bool _v2809(_v2642 _v2424, bkr_i64 _v2776, bkr_i64 _v1289);
bkr_str _v2810(_v2642 _v2424, bkr_str _v2037, _v341 _v1523);
bkr_bool _v2812(_v2642 _v2424, _v428 _v1530);
_v2642 _v2817(_v341 _v1546);
bkr_bool _v2824(bkr_i64 _v1856, bkr_i64 _v387);
bkr_bool _v2825(bkr_i64 _v1856, bkr_i64 _v387);
bkr_bool _v2826(bkr_i64 _v1856, bkr_i64 _v387);
bkr_i64 _v2827(bkr_i64 _v1244);
bkr_bool _v2829(bkr_str _v2830, bkr_i64 _v2831);
bkr_bool _v2839(bkr_str _v1598);
bkr_str _v2842(bkr_str _v1598);
bkr_bool _v2843(bkr_str _v2844);
bkr_bool _v2845(bkr_str _v2844);
bkr_bool _v2846(bkr_str _v2844);
bkr_bool _v2849(bkr_str _v2844);
bkr_bool _v2850(bkr_str _v2844);
bkr_str _v2851(bkr_str _v2852, bkr_str _v2844);
bkr_str _v2853(bkr_str _v2854);
bkr_bool _v2856(bkr_i64 _v2729, bkr_str _v2844);
bkr_str _v2857(bkr_str _v2858, bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852);
bkr_str _v2863(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852);
bkr_str _v2865(bkr_str _v1212);
bkr_str _v2866(bkr_str _v1212, bkr_str _v2852);
bkr_str _v2867(bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852);
bkr_str _v2868(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852);
bkr_str _v2869(bkr_str _v1212);
bkr_str _v2870(bkr_str _v1212, bkr_str _v2852);
bkr_str _v2871(bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852);
bkr_str _v2872(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852);
bkr_str _v2874(bkr_str _v1212);
bkr_str _v2875(bkr_str _v1212, bkr_str _v2852);
bkr_i64 _v2876(bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852);
bkr_i64 _v2877(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852);
bkr_i64 _v2878(bkr_str _v1212);
bkr_i64 _v2879(bkr_str _v1212, bkr_str _v2852);
bkr_str _v2880(bkr_str _v1196, bkr_str _v558);
bkr_str _v2881(bkr_str _v1196, bkr_str _v423);
bkr_str _v2882(bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852);
bkr_str _v2883(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852);
bkr_str _v2884(bkr_str _v1212);
bkr_str _v2885(bkr_str _v1212, bkr_str _v2852);
bkr_str _v2886(bkr_str _v2887, bkr_str _v2888, bkr_str _v2889, bkr_str _v2532);
bkr_str _v2890(bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852);
bkr_str _v2891(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852);
bkr_str _v2892(bkr_str _v1212, bkr_str _v2852);
bkr_i64 _v2893(bkr_str _v2894, bkr_str _v2532);
bkr_i64 _v2896(bkr_str _v1212, bkr_str _v2852, bkr_str _v2532);
bkr_i64 _v2897(bkr_str _v1212, bkr_str _v2852);
bkr_i64 _v2898(bkr_str _v1212, bkr_i64 _v1289);
bkr_i64 _v2899(bkr_str _v1212, bkr_i64 _v1289);
bkr_str _v2901(bkr_str _v1212, bkr_i64 _v1289);
bkr_str _v2903(bkr_str _v330, bkr_str _v1244, bkr_str _v2501, bkr_i64 _v1950, bkr_i64 _v1951, bkr_i64 _v2904, bkr_i64 _v2905, bkr_str _v2906, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117);
bkr_str _v2907(bkr_str _v330, bkr_str _v1244, bkr_str _v2501, bkr_i64 _v1950, bkr_i64 _v1951, bkr_i64 _v2904, bkr_i64 _v2905, bkr_str _v2906, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117, bkr_bool _v2908, bkr_str _v2909);
bkr_str _v2910(bkr_i64 _v2911);
bkr_str _v2912(bkr_str _v1244, bkr_str _v2913, bkr_str _v330, bkr_str _v2914);
bkr_str _v2915(void);
bkr_str _v2916(void);
bkr_str _v2917(void);
bkr_str _v2918(bkr_str _v1212);
bkr_str _v2919(bkr_str _v1212, bkr_str _v2852);
bkr_str _v2922(bkr_str _v1212);
bkr_str _v2923(bkr_str _v1212, bkr_str _v2852);
bkr_str _v2924(bkr_str _v2920);
bkr_str _v2926(bkr_str _v2921);
bkr_str _v2927(bkr_str _v1212, _v1249 _v1261);
bkr_bool _v2957(void);
bkr_i64 _v2958(bkr_str _v2913);
bkr_str _v2961(bkr_str _v1212);
bkr_str _v2962(bkr_str _v1212, bkr_str _v2963);
bkr_bool _v2975(bkr_str _v2976);
bkr_str _v2979(bkr_str _v1841, bkr_str _v2980);
bkr_str _v2984(bkr_str _v1305);
bkr_str _v2987(void);
bkr_bool _v2992(bkr_str _v2976);
bkr_bool _v2996(bkr_str _v2830);
bkr_str _v2997(void);
bkr_bool _v2998(bkr_str _v2999, bkr_str _v3000);
bkr_bool _v3004(void);
bkr_i32 _v3005(void);

bkr_str _v318(bkr_i64 _v319) {
    if ((_v319 == 1)) {
        return "kernel";
    }
    if ((_v319 == 2)) {
        return "function";
    }
    if ((_v319 == 3)) {
        return "parameter";
    }
    if ((_v319 == 4)) {
        return "type";
    }
    if ((_v319 == 5)) {
        return "block";
    }
    if ((_v319 == 6)) {
        return "let";
    }
    if ((_v319 == 7)) {
        return "return";
    }
    if ((_v319 == 8)) {
        return "if";
    }
    if ((_v319 == 9)) {
        return "while";
    }
    if ((_v319 == 10)) {
        return "expression statement";
    }
    if ((_v319 == 11)) {
        return "assignment";
    }
    if ((_v319 == 12)) {
        return "break";
    }
    if ((_v319 == 13)) {
        return "continue";
    }
    if ((_v319 == 14)) {
        return "for";
    }
    if ((_v319 == 15)) {
        return "loop";
    }
    if ((_v319 == 16)) {
        return "defer";
    }
    if (((_v319 == 17) || (_v319 == 18))) {
        return "array repeat";
    }
    if ((_v319 == 18)) {
        return "try";
    }
    if ((_v319 == 19)) {
        return "cast expression";
    }
    if ((_v319 == 20)) {
        return "binary expression";
    }
    if ((_v319 == 21)) {
        return "unary expression";
    }
    if ((_v319 == 22)) {
        return "call expression";
    }
    if ((_v319 == 23)) {
        return "identifier";
    }
    if ((_v319 == 24)) {
        return "integer literal";
    }
    if ((_v319 == 25)) {
        return "boolean literal";
    }
    if ((_v319 == 26)) {
        return "string literal";
    }
    if ((_v319 == 27)) {
        return "constant";
    }
    if ((_v319 == 28)) {
        return "ternary expression";
    }
    if ((_v319 == 29)) {
        return "float literal";
    }
    if ((_v319 == 30)) {
        return "array literal";
    }
    if ((_v319 == 31)) {
        return "index expression";
    }
    if ((_v319 == 32)) {
        return "struct";
    }
    if ((_v319 == 37)) {
        return "enum";
    }
    if ((_v319 == 33)) {
        return "field";
    }
    if ((_v319 == 34)) {
        return "field access";
    }
    if ((_v319 == 35)) {
        return "struct literal";
    }
    if ((_v319 == 36)) {
        return "match expression";
    }
    if ((_v319 == 38)) {
        return "type alias";
    }
    if ((_v319 == 39)) {
        return "method call";
    }
    return bkr_str_concat("node ", int_to_string(_v319));
}

bkr_str _v324(bkr_i64 _v319) {
    if ((_v319 == 0)) {
        return "EOF";
    }
    if ((_v319 == 1)) {
        return "invalid token (unknown character or escape sequence)";
    }
    if ((_v319 == 10)) {
        return "identifier";
    }
    if ((_v319 == 11)) {
        return "integer";
    }
    if ((_v319 == 12)) {
        return "string";
    }
    if ((_v319 == 13)) {
        return "float";
    }
    if ((_v319 == 14)) {
        return "true";
    }
    if ((_v319 == 15)) {
        return "false";
    }
    if ((_v319 == 20)) {
        return "kernel";
    }
    if ((_v319 == 21)) {
        return "enum";
    }
    if ((_v319 == 22)) {
        return "struct";
    }
    if ((_v319 == 23)) {
        return "fn";
    }
    if ((_v319 == 24)) {
        return "let";
    }
    if ((_v319 == 25)) {
        return "if";
    }
    if ((_v319 == 26)) {
        return "else";
    }
    if ((_v319 == 27)) {
        return "for";
    }
    if ((_v319 == 28)) {
        return "in";
    }
    if ((_v319 == 29)) {
        return "while";
    }
    if ((_v319 == 30)) {
        return "break";
    }
    if ((_v319 == 31)) {
        return "continue";
    }
    if ((_v319 == 32)) {
        return "loop";
    }
    if ((_v319 == 33)) {
        return "return";
    }
    if ((_v319 == 34)) {
        return "match";
    }
    if ((_v319 == 35)) {
        return "const";
    }
    if ((_v319 == 36)) {
        return "defer";
    }
    if ((_v319 == 37)) {
        return "type";
    }
    if ((_v319 == 38)) {
        return "as";
    }
    if ((_v319 == 60)) {
        return "i32";
    }
    if ((_v319 == 61)) {
        return "i64";
    }
    if ((_v319 == 62)) {
        return "f64";
    }
    if ((_v319 == 63)) {
        return "bool";
    }
    if ((_v319 == 64)) {
        return "str";
    }
    if ((_v319 == 80)) {
        return "+";
    }
    if ((_v319 == 81)) {
        return "-";
    }
    if ((_v319 == 82)) {
        return "*";
    }
    if ((_v319 == 83)) {
        return "/";
    }
    if ((_v319 == 84)) {
        return "%";
    }
    if ((_v319 == 85)) {
        return "==";
    }
    if ((_v319 == 86)) {
        return "!=";
    }
    if ((_v319 == 87)) {
        return "<";
    }
    if ((_v319 == 88)) {
        return ">";
    }
    if ((_v319 == 89)) {
        return "<=";
    }
    if ((_v319 == 90)) {
        return ">=";
    }
    if ((_v319 == 91)) {
        return "&&";
    }
    if ((_v319 == 92)) {
        return "||";
    }
    if ((_v319 == 93)) {
        return "!";
    }
    if ((_v319 == 94)) {
        return "&";
    }
    if ((_v319 == 95)) {
        return "|";
    }
    if ((_v319 == 96)) {
        return "^";
    }
    if ((_v319 == 97)) {
        return "<<";
    }
    if ((_v319 == 98)) {
        return ">>";
    }
    if ((_v319 == 99)) {
        return "=";
    }
    if ((_v319 == 101)) {
        return "->";
    }
    if ((_v319 == 120)) {
        return "=>";
    }
    if ((_v319 == 102)) {
        return "..";
    }
    if ((_v319 == 103)) {
        return "..=";
    }
    if ((_v319 == 104)) {
        return ".";
    }
    if ((_v319 == 110)) {
        return "(";
    }
    if ((_v319 == 111)) {
        return ")";
    }
    if ((_v319 == 112)) {
        return "{";
    }
    if ((_v319 == 113)) {
        return "}";
    }
    if ((_v319 == 114)) {
        return "[";
    }
    if ((_v319 == 115)) {
        return "]";
    }
    if ((_v319 == 116)) {
        return ",";
    }
    if ((_v319 == 117)) {
        return ";";
    }
    if ((_v319 == 118)) {
        return ":";
    }
    if ((_v319 == 121)) {
        return "::";
    }
    if ((_v319 == 119)) {
        return "?";
    }
    return bkr_str_concat("token ", int_to_string(_v319));
}

bkr_bool _v325(bkr_i64 _v319) {
    return ((((((((((((((((((((((_v319 == 10) || (_v319 == 20)) || (_v319 == 21)) || (_v319 == 22)) || (_v319 == 23)) || (_v319 == 24)) || (_v319 == 25)) || (_v319 == 26)) || (_v319 == 27)) || (_v319 == 28)) || (_v319 == 29)) || (_v319 == 30)) || (_v319 == 31)) || (_v319 == 32)) || (_v319 == 33)) || (_v319 == 34)) || (_v319 == 35)) || (_v319 == 60)) || (_v319 == 61)) || (_v319 == 62)) || (_v319 == 63)) || (_v319 == 64));
}

bkr_str _v327(bkr_i64 _v319) {
    if ((_v319 == 0)) {
        return "i32";
    }
    if ((_v319 == 1)) {
        return "i64";
    }
    if ((_v319 == 2)) {
        return "f64";
    }
    if ((_v319 == 3)) {
        return "bool";
    }
    if ((_v319 == 4)) {
        return "str";
    }
    if ((_v319 == 5)) {
        return "void";
    }
    if ((_v319 == 6)) {
        return "array";
    }
    if ((_v319 == 7)) {
        return "struct";
    }
    if ((_v319 == 8)) {
        return "Vec";
    }
    if ((_v319 == 9)) {
        return "HashMap";
    }
    if ((_v319 == 10)) {
        return "Option";
    }
    if ((_v319 == 11)) {
        return "Result";
    }
    if ((_v319 == 12)) {
        return "!";
    }
    if ((_v319 == 13)) {
        return "fn";
    }
    if ((_v319 == _v316)) {
        return "unknown";
    }
    return bkr_str_concat("type ", int_to_string(_v319));
}

bkr_str _v328(bkr_i64 _v319) {
    if ((_v319 == 1)) {
        return "integer pattern";
    }
    if ((_v319 == 2)) {
        return "boolean pattern";
    }
    if ((_v319 == 3)) {
        return "binding pattern";
    }
    if ((_v319 == 4)) {
        return "wildcard pattern";
    }
    if ((_v319 == 5)) {
        return "Some pattern";
    }
    if ((_v319 == 6)) {
        return "None pattern";
    }
    if ((_v319 == 7)) {
        return "enum variant pattern";
    }
    if ((_v319 == 8)) {
        return "Result.Ok pattern";
    }
    if ((_v319 == 9)) {
        return "Result.Err pattern";
    }
    return bkr_str_concat("pattern ", int_to_string(_v319));
}

bkr_str _v329(bkr_i64 _v330) {
    if ((_v330 == _v263)) {
        return "item";
    }
    if ((_v330 == _v264)) {
        return "statement";
    }
    if ((_v330 == _v265)) {
        return "expression";
    }
    if ((_v330 == _v266)) {
        return "type";
    }
    if ((_v330 == _v267)) {
        return "declaration";
    }
    return "unknown";
}

bkr_i64 _v331(bkr_i64 _v319) {
    if (((((((_v319 == 1) || (_v319 == 2)) || (_v319 == 27)) || (_v319 == 32)) || (_v319 == 37)) || (_v319 == 38))) {
        return _v263;
    }
    if (((((((((((((_v319 == 5) || (_v319 == 6)) || (_v319 == 7)) || (_v319 == 8)) || (_v319 == 9)) || (_v319 == 10)) || (_v319 == 11)) || (_v319 == 12)) || (_v319 == 13)) || (_v319 == 14)) || (_v319 == 15)) || (_v319 == 16))) {
        return _v264;
    }
    if (((((((((((((((((((_v319 == 20) || (_v319 == 21)) || (_v319 == 22)) || (_v319 == 23)) || (_v319 == 24)) || (_v319 == 25)) || (_v319 == 26)) || (_v319 == 28)) || (_v319 == 29)) || (_v319 == 30)) || (_v319 == 31)) || (_v319 == 34)) || (_v319 == 35)) || (_v319 == 36)) || (_v319 == 17)) || (_v319 == 18)) || (_v319 == 19)) || (_v319 == 39))) {
        return _v265;
    }
    if ((_v319 == 4)) {
        return _v266;
    }
    if (((_v319 == 3) || (_v319 == 33))) {
        return _v267;
    }
    return _v262;
}

bkr_bool _v332(bkr_i64 _v319) {
    return (_v331(_v319) == _v263);
}

bkr_bool _v333(bkr_i64 _v319) {
    return (_v331(_v319) == _v264);
}

bkr_bool _v334(bkr_i64 _v319) {
    return (_v331(_v319) == _v265);
}

bkr_bool _v335(bkr_i64 _v319) {
    return (_v331(_v319) == _v266);
}

bkr_bool _v336(bkr_i64 _v319) {
    return (_v331(_v319) == _v267);
}

_v341 _v445(bkr_i64 _v319) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v319);
    vec_push(_v447, _v268);
    vec_push(_v447, _v268);
    return (_v341){._v342 = ((bkr_i64)(_v447))};
}

_v341 _v451(_v341 _v452, bkr_i64 _v387) {
    vec_push(_v453(_v452), _v387);
    return _v452;
}

_v341 _v454(_v341 _v452, bkr_i64 _v339, bkr_i64 _v340) {
    bkr_i64 _v447 = _v453(_v452);
    vec_set(_v447, _v269, _v339);
    vec_set(_v447, _v270, _v340);
    return _v452;
}

_v341 _v456(_v341 _v452, _v338 _v457) {
    return _v454(_v452, _v457._v339, _v457._v340);
}

_v430 _v458(bkr_i64 _v319, bkr_i64 _v387) {
    return _v459(_v319, _v387, 0);
}

_v430 _v459(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345) {
    return _v460(_v319, _v387, _v345, (-1));
}

_v430 _v460(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431) {
    return _v461(_v319, _v387, _v345, _v431, (-1));
}

_v430 _v461(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431, bkr_i64 _v432) {
    return (_v430){._v319 = _v319, ._v339 = _v268, ._v340 = _v268, ._v387 = _v387, ._v345 = _v345, ._v431 = _v431, ._v432 = _v432};
}

bkr_i64 _v462(_v430 _v463) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v463._v319);
    vec_push(_v447, _v463._v339);
    vec_push(_v447, _v463._v340);
    vec_push(_v447, _v463._v387);
    vec_push(_v447, _v463._v345);
    vec_push(_v447, _v463._v431);
    vec_push(_v447, _v463._v432);
    return _v447;
}

_v430 _v464(bkr_i64 _v447) {
    bkr_i64 _v345 = 0;
    bkr_i64 _v431 = (-1);
    bkr_i64 _v432 = (-1);
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v345 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v431 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v432 = vec_get(_v447, (_v272 + 3));
    }
    return (_v430){._v319 = vec_get(_v447, 0), ._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v387 = vec_get(_v447, _v272), ._v345 = _v345, ._v431 = _v431, ._v432 = _v432};
}

_v433 _v468(bkr_i64 _v319, bkr_i64 _v387) {
    return _v469(_v319, _v387, 0);
}

_v433 _v469(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345) {
    _v430 _v463 = _v459(_v319, _v387, _v345);
    return (_v433){._v342 = ((bkr_i64)(_v462(_v463)))};
}

_v433 _v470(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431) {
    _v430 _v463 = _v460(_v319, _v387, _v345, _v431);
    return (_v433){._v342 = ((bkr_i64)(_v462(_v463)))};
}

_v433 _v471(bkr_i64 _v319, bkr_i64 _v387, bkr_i64 _v345, bkr_i64 _v431, bkr_i64 _v432) {
    _v430 _v463 = _v461(_v319, _v387, _v345, _v431, _v432);
    return (_v433){._v342 = ((bkr_i64)(_v462(_v463)))};
}

_v433 _v472(_v433 _v473, bkr_i64 _v339, bkr_i64 _v340) {
    bkr_i64 _v463 = _v474(_v473);
    vec_set(_v463, _v269, _v339);
    vec_set(_v463, _v270, _v340);
    return _v473;
}

bkr_i64 _v475(bkr_i64 _v319) {
    return _v453(_v445(_v319));
}

bkr_i64 _v476(bkr_i64 _v447, bkr_i64 _v387) {
    _v451(_v477(_v447), _v387);
    return _v447;
}

bkr_i64 _v478(bkr_i64 _v447) {
    return vec_get(_v447, 0);
}

bkr_i64 _v479(bkr_i64 _v447) {
    return _v478(_v447);
}

_v338 _v480(bkr_i64 _v339, bkr_i64 _v340) {
    return (_v338){._v339 = _v339, ._v340 = _v340};
}

_v338 _v481(void) {
    return _v480(_v268, _v268);
}

bkr_i64 _v482(_v338 _v457) {
    return _v457._v339;
}

bkr_i64 _v483(_v338 _v457) {
    return _v457._v340;
}

bkr_bool _v484(_v338 _v457) {
    return ((_v457._v339 != _v268) && (_v457._v340 != _v268));
}

bkr_i64 _v485(bkr_i64 _v447) {
    return vec_get(_v447, _v269);
}

bkr_i64 _v486(bkr_i64 _v447) {
    return vec_get(_v447, _v270);
}

_v338 _v487(bkr_i64 _v447) {
    return _v480(_v485(_v447), _v486(_v447));
}

bkr_bool _v488(bkr_i64 _v447) {
    return _v484(_v487(_v447));
}

bkr_i64 _v489(bkr_i64 _v447, bkr_i64 _v339, bkr_i64 _v340) {
    _v454(_v477(_v447), _v339, _v340);
    return _v447;
}

bkr_i64 _v490(bkr_i64 _v447, _v338 _v457) {
    _v456(_v477(_v447), _v457);
    return _v447;
}

bkr_bool _v491(bkr_i64 _v447, bkr_i64 _v362) {
    return (vec_len(_v447) > (_v362 + _v271));
}

bkr_i64 _v492(bkr_i64 _v447) {
    return _v331(_v478(_v447));
}

bkr_bool _v493(bkr_i64 _v447) {
    return _v332(_v478(_v447));
}

bkr_bool _v494(bkr_i64 _v447) {
    return _v333(_v478(_v447));
}

bkr_bool _v495(bkr_i64 _v447) {
    return _v334(_v478(_v447));
}

bkr_bool _v496(bkr_i64 _v447) {
    return _v335(_v478(_v447));
}

bkr_str _v497(bkr_i64 _v447) {
    bkr_i64 _v330 = _v492(_v447);
    return bkr_str_concat(bkr_str_concat(_v329(_v330), ":"), _v318(_v478(_v447)));
}

bkr_bool _v498(bkr_i64 _v447) {
    return (_v478(_v447) == _v245);
}

bkr_bool _v499(bkr_i64 _v447) {
    return (_v478(_v447) == _v244);
}

bkr_bool _v500(bkr_i64 _v447) {
    return (_v478(_v447) == _v227);
}

bkr_bool _v501(bkr_i64 _v447) {
    return (_v478(_v447) == _v232);
}

bkr_bool _v502(bkr_i64 _v447) {
    return (_v478(_v447) == _v224);
}

bkr_bool _v503(bkr_i64 _v447) {
    return (_v478(_v447) == _v249);
}

bkr_bool _v504(bkr_i64 _v447) {
    return (_v478(_v447) == _v254);
}

bkr_i64 _v505(bkr_i64 _v447, bkr_i64 _v362) {
    return vec_get(_v447, (_v362 + _v271));
}

bkr_i64 _v506(bkr_i64 _v447) {
    return ((bkr_i64)(_v447));
}

_v341 _v507(bkr_i64 _v342) {
    return (_v341){._v342 = _v342};
}

_v341 _v477(bkr_i64 _v447) {
    return _v507(_v506(_v447));
}

bkr_i64 _v508(_v341 _v452) {
    return _v452._v342;
}

bkr_i64 _v453(_v341 _v452) {
    return _v509(_v508(_v452));
}

bkr_i64 _v510(_v341 _v452) {
    return _v479(_v453(_v452));
}

bkr_i64 _v511(_v341 _v452) {
    return _v492(_v453(_v452));
}

bkr_i64 _v512(_v341 _v452) {
    return _v485(_v453(_v452));
}

bkr_i64 _v513(_v341 _v452) {
    return _v486(_v453(_v452));
}

bkr_i64 _v509(bkr_i64 _v342) {
    return ((bkr_i64)(_v342));
}

_v341 _v514(bkr_i64 _v342) {
    return _v507(_v342);
}

bkr_i64 _v515(bkr_i64 _v516) {
    return _v506(_v516);
}

_v346 _v517(bkr_i64 _v342) {
    return (_v346){._v342 = _v342};
}

_v346 _v518(bkr_i64 _v516) {
    return _v517(_v515(_v516));
}

_v346 _v519(_v341 _v452) {
    return _v517(_v508(_v452));
}

bkr_i64 _v520(_v346 _v521) {
    return _v521._v342;
}

bkr_i64 _v522(_v346 _v521) {
    return _v520(_v521);
}

bkr_bool _v523(_v346 _v521) {
    return _v524(_v520(_v521));
}

bkr_bool _v525(_v346 _v521) {
    return _v526(_v520(_v521));
}

bkr_i64 _v527(_v346 _v521) {
    return _v509(_v520(_v521));
}

_v343 _v528(_v346 _v521) {
    return _v529(_v527(_v521));
}

bkr_i64 _v530(_v346 _v521) {
    _v343 _v531 = _v528(_v521);
    return _v531._v319;
}

bkr_i64 _v532(_v346 _v521) {
    _v343 _v531 = _v528(_v521);
    if ((_v531._v319 == 7)) {
        return _v531._v344;
    }
    return (-1);
}

bkr_i64 _v533(_v346 _v521) {
    _v343 _v531 = _v528(_v521);
    if (((_v531._v319 == 6) || (_v531._v319 == 8))) {
        return _v531._v344;
    }
    return _v316;
}

bkr_i64 _v534(_v346 _v521) {
    _v343 _v531 = _v528(_v521);
    if ((_v531._v319 == 6)) {
        return _v531._v345;
    }
    return (-1);
}

bkr_i64 _v535(_v346 _v521) {
    _v343 _v531 = _v528(_v521);
    return _v531._v344;
}

bkr_i64 _v536(_v346 _v521) {
    _v343 _v531 = _v528(_v521);
    return _v531._v345;
}

bkr_i64 _v537(bkr_i64 _v368) {
    return _v506(_v368);
}

_v426 _v538(bkr_i64 _v342) {
    return (_v426){._v342 = _v342};
}

_v426 _v539(bkr_i64 _v368) {
    return _v538(_v537(_v368));
}

_v426 _v540(_v341 _v452) {
    return _v538(_v508(_v452));
}

bkr_i64 _v541(_v426 _v542) {
    return _v542._v342;
}

bkr_i64 _v543(_v426 _v542) {
    return _v541(_v542);
}

bkr_i64 _v544(_v426 _v542) {
    return _v509(_v541(_v542));
}

bkr_i64 _v545(_v426 _v542) {
    return _v479(_v544(_v542));
}

bkr_i64 _v546(_v426 _v542) {
    return _v512(_v547(_v542));
}

bkr_i64 _v548(_v426 _v542) {
    return _v513(_v547(_v542));
}

bkr_i64 _v549(bkr_i64 _v370) {
    return _v506(_v370);
}

_v427 _v550(bkr_i64 _v342) {
    return (_v427){._v342 = _v342};
}

_v427 _v551(bkr_i64 _v370) {
    return _v550(_v549(_v370));
}

_v427 _v552(_v341 _v452) {
    return _v550(_v508(_v452));
}

bkr_i64 _v553(_v427 _v554) {
    return _v554._v342;
}

bkr_i64 _v555(_v427 _v554) {
    return _v509(_v553(_v554));
}

bkr_i64 _v556(_v427 _v554) {
    return _v479(_v555(_v554));
}

bkr_i64 _v557(bkr_i64 _v558) {
    return _v506(_v558);
}

_v428 _v559(bkr_i64 _v342) {
    return (_v428){._v342 = _v342};
}

_v428 _v560(bkr_i64 _v558) {
    return _v559(_v557(_v558));
}

_v428 _v561(_v341 _v452) {
    return _v559(_v508(_v452));
}

bkr_i64 _v562(_v428 _v563) {
    return _v563._v342;
}

_v428 _v564(void) {
    return _v559(_v565());
}

bkr_bool _v566(_v428 _v563) {
    return _v524(_v562(_v563));
}

bkr_bool _v567(_v428 _v563) {
    return _v526(_v562(_v563));
}

bkr_i64 _v568(_v428 _v563) {
    return _v509(_v562(_v563));
}

bkr_i64 _v569(_v428 _v563) {
    return _v479(_v568(_v563));
}

_v338 _v570(_v426 _v542) {
    return _v487(_v544(_v542));
}

_v338 _v571(_v427 _v554) {
    return _v487(_v555(_v554));
}

_v338 _v572(_v428 _v563) {
    return _v487(_v568(_v563));
}

bkr_i64 _v573(_v426 _v542) {
    bkr_i64 _v574 = _v545(_v542);
    if ((((((_v574 == 24) || (_v574 == 29)) || (_v574 == 25)) || (_v574 == 26)) || (_v574 == 23))) {
        return 0;
    }
    if ((_v574 == 20)) {
        return 1;
    }
    if ((_v574 == 21)) {
        return 2;
    }
    if ((_v574 == 22)) {
        return 3;
    }
    if ((_v574 == 39)) {
        return 4;
    }
    if ((_v574 == 31)) {
        return 5;
    }
    if ((_v574 == 34)) {
        return 6;
    }
    if ((_v574 == 19)) {
        return 7;
    }
    if ((_v574 == 28)) {
        return 8;
    }
    if ((_v574 == 30)) {
        return 9;
    }
    if ((_v574 == 17)) {
        return 10;
    }
    if ((_v574 == 35)) {
        return 11;
    }
    if ((_v574 == 36)) {
        return 12;
    }
    if ((_v574 == 5)) {
        return 13;
    }
    return 14;
}

bkr_i64 _v575(_v427 _v554) {
    bkr_i64 _v574 = _v556(_v554);
    if ((_v574 == 6)) {
        return 0;
    }
    if ((_v574 == 11)) {
        return 1;
    }
    if ((_v574 == 10)) {
        return 2;
    }
    if ((_v574 == 7)) {
        return 3;
    }
    if ((_v574 == 16)) {
        return 4;
    }
    if ((_v574 == 9)) {
        return 5;
    }
    if ((_v574 == 14)) {
        return 6;
    }
    if ((_v574 == 15)) {
        return 7;
    }
    if ((_v574 == 12)) {
        return 8;
    }
    if ((_v574 == 13)) {
        return 9;
    }
    return 10;
}

bkr_i64 _v576(_v428 _v563) {
    bkr_i64 _v574 = _v569(_v563);
    if ((_v574 == 2)) {
        return 0;
    }
    if ((_v574 == 27)) {
        return 1;
    }
    if ((_v574 == 32)) {
        return 2;
    }
    if ((_v574 == 37)) {
        return 3;
    }
    if ((_v574 == 38)) {
        return 4;
    }
    if ((_v574 == 1)) {
        return 5;
    }
    return 6;
}

bkr_i64 _v577(bkr_i64 _v578) {
    return _v506(_v578);
}

_v429 _v579(bkr_i64 _v342) {
    return (_v429){._v342 = _v342};
}

_v429 _v580(bkr_i64 _v578) {
    return _v579(_v577(_v578));
}

_v429 _v581(_v341 _v452) {
    return _v579(_v508(_v452));
}

bkr_i64 _v582(_v429 _v583) {
    return _v583._v342;
}

bkr_i64 _v584(_v429 _v583) {
    return _v582(_v583);
}

bkr_i64 _v585(_v429 _v583) {
    return _v509(_v582(_v583));
}

_v341 _v586(_v346 _v521) {
    return _v507(_v520(_v521));
}

_v341 _v547(_v426 _v542) {
    return _v507(_v541(_v542));
}

_v341 _v587(_v427 _v554) {
    return _v507(_v553(_v554));
}

_v341 _v588(_v428 _v563) {
    return _v507(_v562(_v563));
}

_v341 _v589(_v429 _v583) {
    return _v507(_v582(_v583));
}

bkr_i64 _v590(_v429 _v583) {
    return (vec_len(_v585(_v583)) - _v272);
}

bkr_i64 _v591(bkr_i64 _v463) {
    return ((bkr_i64)(_v463));
}

_v433 _v592(bkr_i64 _v342) {
    return (_v433){._v342 = _v342};
}

_v433 _v593(bkr_i64 _v463) {
    return _v592(_v591(_v463));
}

bkr_i64 _v594(_v433 _v473) {
    return _v473._v342;
}

bkr_i64 _v474(_v433 _v473) {
    return _v595(_v594(_v473));
}

_v430 _v596(_v433 _v473) {
    return _v464(_v474(_v473));
}

bkr_i64 _v597(_v433 _v473) {
    _v430 _v463 = _v596(_v473);
    return _v463._v319;
}

bkr_i64 _v598(_v433 _v473) {
    _v430 _v463 = _v596(_v473);
    return _v463._v387;
}

bkr_i64 _v599(_v433 _v473) {
    _v430 _v463 = _v596(_v473);
    return _v463._v345;
}

bkr_i64 _v600(_v433 _v473) {
    _v430 _v463 = _v596(_v473);
    return _v463._v431;
}

bkr_i64 _v601(_v433 _v473) {
    _v430 _v463 = _v596(_v473);
    return _v463._v432;
}

bkr_i64 _v602(_v433 _v473) {
    _v430 _v463 = _v596(_v473);
    return _v463._v339;
}

bkr_i64 _v603(_v433 _v473) {
    _v430 _v463 = _v596(_v473);
    return _v463._v340;
}

bkr_i64 _v595(bkr_i64 _v342) {
    return ((bkr_i64)(_v342));
}

_v434 _v604(bkr_i64 _v342) {
    return (_v434){._v342 = _v342};
}

_v434 _v605(bkr_i64 _v606) {
    return _v604(((bkr_i64)(_v606)));
}

bkr_i64 _v607(_v434 _v608) {
    return _v608._v342;
}

bkr_i64 _v609(_v434 _v608) {
    return ((bkr_i64)(_v607(_v608)));
}

bkr_i64 _v610(bkr_i64 _v342) {
    return _v609(_v604(_v342));
}

_v435 _v611(bkr_i64 _v342) {
    return (_v435){._v342 = _v342};
}

_v435 _v612(bkr_i64 _v613) {
    return _v611(((bkr_i64)(_v613)));
}

bkr_i64 _v614(_v435 _v615) {
    return _v615._v342;
}

bkr_i64 _v616(_v435 _v615) {
    return ((bkr_i64)(_v614(_v615)));
}

bkr_i64 _v617(bkr_i64 _v342) {
    return _v616(_v611(_v342));
}

_v436 _v618(bkr_i64 _v342) {
    return (_v436){._v342 = _v342};
}

_v436 _v619(bkr_i64 _v406) {
    return _v618(((bkr_i64)(_v406)));
}

bkr_i64 _v620(_v436 _v621) {
    return _v621._v342;
}

bkr_i64 _v622(_v436 _v621) {
    return ((bkr_i64)(_v620(_v621)));
}

bkr_i64 _v623(bkr_i64 _v342) {
    return _v622(_v618(_v342));
}

_v437 _v624(bkr_i64 _v342) {
    return (_v437){._v342 = _v342};
}

_v437 _v625(bkr_i64 _v613) {
    return _v624(((bkr_i64)(_v613)));
}

bkr_i64 _v626(_v437 _v615) {
    return _v615._v342;
}

bkr_i64 _v627(_v437 _v615) {
    return ((bkr_i64)(_v626(_v615)));
}

bkr_i64 _v628(bkr_i64 _v342) {
    return _v627(_v624(_v342));
}

bkr_i64 _v629(bkr_i64 _v606) {
    return _v607(_v605(_v606));
}

bkr_i64 _v630(bkr_i64 _v613) {
    return _v614(_v612(_v613));
}

bkr_i64 _v631(bkr_i64 _v406) {
    return _v620(_v619(_v406));
}

bkr_i64 _v632(bkr_i64 _v613) {
    return _v626(_v625(_v613));
}

bkr_i64 _v633(bkr_i64 _v606, bkr_i64 _v447) {
    _v634(_v605(_v606), _v447);
    return _v606;
}

_v434 _v634(_v434 _v608, bkr_i64 _v447) {
    vec_push(_v609(_v608), _v506(_v447));
    return _v608;
}

_v434 _v635(_v434 _v608, _v341 _v452) {
    vec_push(_v609(_v608), _v508(_v452));
    return _v608;
}

_v434 _v636(_v434 _v608, _v426 _v542) {
    return _v635(_v608, _v547(_v542));
}

_v434 _v637(_v434 _v608, _v428 _v563) {
    return _v635(_v608, _v588(_v563));
}

_v434 _v638(_v434 _v608, _v429 _v583) {
    return _v635(_v608, _v589(_v583));
}

bkr_i64 _v639(bkr_i64 _v406, bkr_i64 _v463) {
    _v640(_v619(_v406), _v463);
    return _v406;
}

_v436 _v640(_v436 _v621, bkr_i64 _v463) {
    vec_push(_v622(_v621), _v591(_v463));
    return _v621;
}

_v436 _v641(_v436 _v621, _v433 _v473) {
    vec_push(_v622(_v621), _v594(_v473));
    return _v621;
}

bkr_i64 _v642(bkr_i64 _v613, bkr_i64 _v387) {
    _v643(_v612(_v613), _v387);
    return _v613;
}

_v435 _v643(_v435 _v615, bkr_i64 _v387) {
    vec_push(_v616(_v615), _v387);
    return _v615;
}

bkr_i64 _v644(bkr_i64 _v447, bkr_i64 _v362) {
    return _v509(_v505(_v447, _v362));
}

bkr_i64 _v645(bkr_i64 _v447, bkr_i64 _v362) {
    return _v609(_v646(_v447, _v362));
}

_v434 _v646(bkr_i64 _v447, bkr_i64 _v362) {
    return _v604(_v505(_v447, _v362));
}

bkr_i64 _v647(bkr_i64 _v447, bkr_i64 _v362) {
    return _v616(_v648(_v447, _v362));
}

_v435 _v648(bkr_i64 _v447, bkr_i64 _v362) {
    return _v611(_v505(_v447, _v362));
}

bkr_i64 _v649(bkr_i64 _v447, bkr_i64 _v362) {
    return _v622(_v650(_v447, _v362));
}

_v436 _v650(bkr_i64 _v447, bkr_i64 _v362) {
    return _v618(_v505(_v447, _v362));
}

bkr_i64 _v651(bkr_i64 _v447, bkr_i64 _v362) {
    return _v627(_v652(_v447, _v362));
}

_v437 _v652(bkr_i64 _v447, bkr_i64 _v362) {
    return _v624(_v505(_v447, _v362));
}

bkr_i64 _v565(void) {
    return 0;
}

bkr_bool _v524(bkr_i64 _v387) {
    return (_v387 == 0);
}

bkr_bool _v526(bkr_i64 _v387) {
    return (_v387 != 0);
}

bkr_i64 _v653(bkr_i64 _v387) {
    return _v509(_v387);
}

bkr_i64 _v654(bkr_i64 _v516) {
    if (_v524(_v516)) {
        return _v316;
    }
    _v343 _v531 = _v529(_v509(_v516));
    return _v531._v319;
}

bkr_i64 _v655(bkr_i64 _v516) {
    if (_v524(_v516)) {
        return (-1);
    }
    _v343 _v531 = _v529(_v509(_v516));
    if ((_v531._v319 == 7)) {
        return _v531._v344;
    }
    return (-1);
}

bkr_i64 _v656(bkr_i64 _v516) {
    if (_v524(_v516)) {
        return _v316;
    }
    _v343 _v531 = _v529(_v509(_v516));
    if ((_v531._v319 == 6)) {
        return _v531._v344;
    }
    return _v316;
}

bkr_i64 _v657(bkr_i64 _v516) {
    if (_v524(_v516)) {
        return (-1);
    }
    _v343 _v531 = _v529(_v509(_v516));
    if ((_v531._v319 == 6)) {
        return _v531._v345;
    }
    return (-1);
}

bkr_i64 _v658(bkr_i64 _v516) {
    if (_v524(_v516)) {
        return 0;
    }
    _v343 _v531 = _v529(_v509(_v516));
    return _v531._v344;
}

bkr_i64 _v659(bkr_i64 _v516) {
    if (_v524(_v516)) {
        return (-1);
    }
    _v343 _v531 = _v529(_v509(_v516));
    return _v531._v345;
}

bkr_i64 _v660(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

_v347 _v661(_v426 _v542) {
    return _v662(_v544(_v542));
}

bkr_i64 _v663(_v426 _v542) {
    return _v660(_v544(_v542));
}

bkr_i64 _v664(_v341 _v452) {
    return _v660(_v453(_v452));
}

bkr_i64 _v665(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v666(_v426 _v542) {
    return _v665(_v544(_v542));
}

bkr_i64 _v667(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v668(bkr_i64 _v447) {
    return _v505(_v447, 3);
}

bkr_i64 _v669(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

_v348 _v670(_v426 _v542) {
    return _v671(_v544(_v542));
}

bkr_i64 _v672(_v426 _v542) {
    return _v669(_v544(_v542));
}

bkr_i64 _v673(bkr_i64 _v447) {
    return _v644(_v447, 2);
}

bkr_i64 _v674(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v675(_v426 _v542) {
    return _v674(_v544(_v542));
}

bkr_i64 _v676(bkr_i64 _v447) {
    return _v644(_v447, 3);
}

bkr_i64 _v677(bkr_i64 _v447) {
    return _v505(_v447, 3);
}

bkr_i64 _v678(_v426 _v542) {
    return _v677(_v544(_v542));
}

bkr_i64 _v679(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

_v352 _v680(_v426 _v542) {
    return _v681(_v544(_v542));
}

bkr_i64 _v682(_v426 _v542) {
    return _v679(_v544(_v542));
}

bkr_i64 _v683(bkr_i64 _v447) {
    return _v644(_v447, 2);
}

bkr_i64 _v684(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v685(_v426 _v542) {
    return _v684(_v544(_v542));
}

bkr_i64 _v686(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

_v354 _v687(_v426 _v542) {
    return _v688(_v544(_v542));
}

bkr_i64 _v689(_v426 _v542) {
    return _v686(_v544(_v542));
}

bkr_i64 _v690(bkr_i64 _v447) {
    return _v609(_v691(_v447));
}

_v434 _v691(bkr_i64 _v447) {
    return _v646(_v447, 2);
}

_v434 _v692(_v426 _v542) {
    return _v691(_v544(_v542));
}

bkr_i64 _v693(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v694(_v426 _v542) {
    return _v693(_v544(_v542));
}

_v426 _v695(_v426 _v542) {
    return _v538(_v693(_v544(_v542)));
}

bkr_i64 _v696(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v697(_v426 _v542) {
    return _v696(_v544(_v542));
}

_v434 _v698(bkr_i64 _v447) {
    return _v646(_v447, 3);
}

_v434 _v699(_v426 _v542) {
    return _v698(_v544(_v542));
}

bkr_i64 _v700(bkr_i64 _v447) {
    return _v609(_v701(_v447));
}

_v434 _v701(bkr_i64 _v447) {
    return _v646(_v447, 1);
}

_v434 _v702(_v426 _v542) {
    return _v701(_v544(_v542));
}

bkr_i64 _v703(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v704(_v426 _v542) {
    return _v703(_v544(_v542));
}

_v426 _v705(_v426 _v542) {
    return _v538(_v704(_v542));
}

bkr_i64 _v706(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v707(_v426 _v542) {
    return _v706(_v544(_v542));
}

bkr_i64 _v708(bkr_i64 _v447) {
    return _v644(_v447, 1);
}

bkr_i64 _v709(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

_v360 _v710(_v426 _v542) {
    return _v711(_v544(_v542));
}

bkr_i64 _v712(_v426 _v542) {
    return _v709(_v544(_v542));
}

bkr_i64 _v713(bkr_i64 _v447) {
    return _v644(_v447, 2);
}

bkr_i64 _v714(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v715(_v426 _v542) {
    return _v714(_v544(_v542));
}

bkr_i64 _v716(bkr_i64 _v447) {
    return _v644(_v447, 1);
}

bkr_i64 _v717(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

_v363 _v718(_v426 _v542) {
    return _v719(_v544(_v542));
}

bkr_i64 _v720(_v426 _v542) {
    return _v717(_v544(_v542));
}

_v426 _v721(_v426 _v542) {
    return _v538(_v720(_v542));
}

bkr_i64 _v722(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v723(_v426 _v542) {
    return _v722(_v544(_v542));
}

bkr_i64 _v724(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v725(_v426 _v542) {
    return _v724(_v544(_v542));
}

bkr_i64 _v726(bkr_i64 _v447) {
    return _v616(_v727(_v447));
}

_v435 _v727(bkr_i64 _v447) {
    return _v648(_v447, 2);
}

_v435 _v728(_v426 _v542) {
    return _v727(_v544(_v542));
}

bkr_i64 _v729(bkr_i64 _v447) {
    return _v609(_v730(_v447));
}

_v434 _v730(bkr_i64 _v447) {
    return _v646(_v447, 3);
}

_v434 _v731(_v426 _v542) {
    return _v730(_v544(_v542));
}

bkr_i64 _v732(bkr_i64 _v447) {
    return _v644(_v447, 1);
}

bkr_i64 _v733(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v734(_v426 _v542) {
    return _v733(_v544(_v542));
}

bkr_i64 _v735(bkr_i64 _v447) {
    return _v644(_v447, 2);
}

bkr_i64 _v736(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v737(_v426 _v542) {
    return _v736(_v544(_v542));
}

bkr_i64 _v738(bkr_i64 _v447) {
    return _v644(_v447, 3);
}

bkr_i64 _v739(bkr_i64 _v447) {
    return _v505(_v447, 3);
}

bkr_i64 _v740(_v426 _v542) {
    return _v739(_v544(_v542));
}

bkr_i64 _v741(bkr_i64 _v447) {
    return _v644(_v447, 1);
}

bkr_i64 _v742(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v743(_v426 _v542) {
    return _v742(_v544(_v542));
}

bkr_i64 _v744(bkr_i64 _v447) {
    return _v622(_v745(_v447));
}

_v436 _v745(bkr_i64 _v447) {
    return _v650(_v447, 2);
}

_v436 _v746(_v426 _v542) {
    return _v745(_v544(_v542));
}

bkr_i64 _v747(bkr_i64 _v447) {
    return _v609(_v748(_v447));
}

_v434 _v748(bkr_i64 _v447) {
    return _v646(_v447, 3);
}

_v434 _v749(_v426 _v542) {
    return _v748(_v544(_v542));
}

_v435 _v750(bkr_i64 _v447) {
    return _v648(_v447, 4);
}

_v435 _v751(_v426 _v542) {
    return _v750(_v544(_v542));
}

bkr_i64 _v752(bkr_i64 _v463) {
    _v430 _v753 = _v464(_v463);
    return _v753._v319;
}

bkr_i64 _v754(bkr_i64 _v463) {
    _v430 _v753 = _v464(_v463);
    return _v753._v387;
}

bkr_i64 _v755(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

_v364 _v756(_v427 _v554) {
    return _v757(_v555(_v554));
}

bkr_i64 _v758(_v427 _v554) {
    return _v755(_v555(_v554));
}

bkr_i64 _v759(bkr_i64 _v447) {
    return _v760(_v447);
}

bkr_i64 _v760(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v761(_v427 _v554) {
    return _v760(_v555(_v554));
}

bkr_i64 _v762(bkr_i64 _v447) {
    return _v763(_v447);
}

bkr_i64 _v763(bkr_i64 _v447) {
    return _v505(_v447, 3);
}

bkr_i64 _v764(_v427 _v554) {
    return _v763(_v555(_v554));
}

bkr_i64 _v765(bkr_i64 _v447) {
    return _v766(_v447);
}

bkr_i64 _v766(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

_v367 _v767(_v427 _v554) {
    return _v768(_v555(_v554));
}

bkr_i64 _v769(_v427 _v554) {
    return _v766(_v555(_v554));
}

bkr_i64 _v770(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

_v369 _v771(_v427 _v554) {
    return _v772(_v555(_v554));
}

bkr_i64 _v773(_v427 _v554) {
    return _v770(_v555(_v554));
}

_v427 _v774(_v427 _v554) {
    return _v550(_v773(_v554));
}

bkr_i64 _v775(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

_v371 _v776(_v426 _v542) {
    return _v777(_v544(_v542));
}

bkr_i64 _v778(_v426 _v542) {
    return _v775(_v544(_v542));
}

_v426 _v779(_v426 _v542) {
    return _v538(_v778(_v542));
}

bkr_i64 _v780(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v781(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v782(_v426 _v542) {
    return _v780(_v544(_v542));
}

bkr_i64 _v783(_v426 _v542) {
    return _v781(_v544(_v542));
}

_v426 _v784(_v426 _v542) {
    return _v538(_v782(_v542));
}

_v346 _v785(_v426 _v542) {
    return _v517(_v783(_v542));
}

_v374 _v786(_v427 _v554) {
    return _v787(_v555(_v554));
}

_v378 _v788(_v427 _v554) {
    return _v789(_v555(_v554));
}

_v380 _v790(_v427 _v554) {
    return _v791(_v555(_v554));
}

_v384 _v792(_v427 _v554) {
    return _v793(_v555(_v554));
}

_v385 _v794(_v427 _v554) {
    return _v795(_v555(_v554));
}

_v388 _v796(_v427 _v554) {
    return _v797(_v555(_v554));
}

_v389 _v798(_v427 _v554) {
    return _v799(_v555(_v554));
}

_v390 _v800(_v427 _v554) {
    return _v801(_v555(_v554));
}

_v391 _v802(_v429 _v583) {
    return _v803(_v585(_v583));
}

_v392 _v804(_v426 _v542) {
    return _v805(_v544(_v542));
}

_v395 _v806(_v426 _v542) {
    return _v807(_v544(_v542));
}

_v400 _v808(_v426 _v542) {
    return _v809(_v544(_v542));
}

_v404 _v810(_v426 _v542) {
    return _v811(_v544(_v542));
}

_v409 _v812(_v341 _v452) {
    return _v813(_v453(_v452));
}

_v410 _v814(_v428 _v563) {
    return _v815(_v568(_v563));
}

_v413 _v816(_v428 _v563) {
    return _v817(_v568(_v563));
}

_v414 _v818(_v341 _v452) {
    return _v819(_v453(_v452));
}

_v415 _v820(_v428 _v563) {
    return _v821(_v568(_v563));
}

_v417 _v822(_v428 _v563) {
    return _v823(_v568(_v563));
}

_v422 _v824(_v341 _v452) {
    return _v825(_v453(_v452));
}

bkr_i64 _v826(bkr_i64 _v447) {
    return _v644(_v447, 1);
}

bkr_i64 _v827(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v828(_v427 _v554) {
    return _v827(_v555(_v554));
}

bkr_i64 _v829(bkr_i64 _v447) {
    return _v644(_v447, 2);
}

_v429 _v830(_v427 _v554) {
    return _v580(_v829(_v555(_v554)));
}

bkr_i64 _v831(bkr_i64 _v447) {
    return _v832(_v447);
}

bkr_i64 _v832(bkr_i64 _v447) {
    return _v505(_v447, 3);
}

bkr_i64 _v833(_v427 _v554) {
    return _v832(_v555(_v554));
}

bkr_i64 _v834(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v835(_v427 _v554) {
    return _v834(_v555(_v554));
}

bkr_i64 _v836(bkr_i64 _v447) {
    return _v644(_v447, 2);
}

bkr_i64 _v837(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v838(_v427 _v554) {
    return _v837(_v555(_v554));
}

bkr_i64 _v839(bkr_i64 _v447) {
    return _v644(_v447, 3);
}

bkr_i64 _v840(bkr_i64 _v447) {
    return _v505(_v447, 3);
}

bkr_i64 _v841(_v427 _v554) {
    return _v840(_v555(_v554));
}

bkr_i64 _v842(bkr_i64 _v447) {
    return _v505(_v447, 4);
}

bkr_i64 _v843(_v427 _v554) {
    return _v842(_v555(_v554));
}

bkr_i64 _v844(bkr_i64 _v447) {
    return _v644(_v447, 5);
}

_v429 _v845(_v427 _v554) {
    return _v580(_v844(_v555(_v554)));
}

bkr_i64 _v846(bkr_i64 _v447) {
    return _v644(_v447, 1);
}

_v429 _v847(_v427 _v554) {
    return _v580(_v846(_v555(_v554)));
}

bkr_i64 _v848(bkr_i64 _v447) {
    return _v644(_v447, 1);
}

bkr_i64 _v849(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v850(_v427 _v554) {
    return _v849(_v555(_v554));
}

bkr_i64 _v851(bkr_i64 _v447) {
    return _v644(_v447, 2);
}

_v429 _v852(_v427 _v554) {
    return _v580(_v851(_v555(_v554)));
}

bkr_i64 _v853(bkr_i64 _v447) {
    return _v644(_v447, 1);
}

bkr_i64 _v854(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v855(_v427 _v554) {
    return _v854(_v555(_v554));
}

bkr_i64 _v856(bkr_i64 _v447) {
    return _v644(_v447, 2);
}

bkr_i64 _v857(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v858(_v427 _v554) {
    return _v857(_v555(_v554));
}

bkr_i64 _v859(bkr_i64 _v447) {
    return _v644(_v447, 1);
}

bkr_i64 _v860(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v861(_v427 _v554) {
    return _v860(_v555(_v554));
}

bkr_i64 _v862(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v863(_v341 _v452) {
    return _v862(_v453(_v452));
}

bkr_i64 _v864(bkr_i64 _v447) {
    return _v644(_v447, 2);
}

bkr_i64 _v865(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v866(_v341 _v452) {
    return _v865(_v453(_v452));
}

_v346 _v867(_v341 _v452) {
    return _v517(_v866(_v452));
}

bkr_i64 _v868(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v869(_v428 _v563) {
    return _v868(_v568(_v563));
}

bkr_i64 _v870(bkr_i64 _v447) {
    return _v609(_v871(_v447));
}

_v434 _v871(bkr_i64 _v447) {
    return _v646(_v447, 2);
}

_v434 _v872(_v428 _v563) {
    return _v871(_v568(_v563));
}

bkr_i64 _v873(bkr_i64 _v447) {
    return _v874(_v447);
}

bkr_i64 _v874(bkr_i64 _v447) {
    return _v505(_v447, 3);
}

bkr_i64 _v875(_v428 _v563) {
    return _v874(_v568(_v563));
}

bkr_i64 _v876(bkr_i64 _v447) {
    return _v644(_v447, 4);
}

_v429 _v877(_v428 _v563) {
    return _v580(_v876(_v568(_v563)));
}

bkr_i64 _v878(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v879(_v428 _v563) {
    return _v878(_v568(_v563));
}

bkr_i64 _v880(bkr_i64 _v447) {
    return _v881(_v447);
}

bkr_i64 _v881(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v882(_v428 _v563) {
    return _v881(_v568(_v563));
}

bkr_i64 _v883(bkr_i64 _v447) {
    return _v884(_v447);
}

bkr_i64 _v884(bkr_i64 _v447) {
    return _v505(_v447, 3);
}

bkr_i64 _v885(_v428 _v563) {
    return _v884(_v568(_v563));
}

bkr_i64 _v886(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v887(_v428 _v563) {
    return _v886(_v568(_v563));
}

bkr_i64 _v888(bkr_i64 _v447) {
    return _v609(_v889(_v447));
}

_v434 _v889(bkr_i64 _v447) {
    return _v646(_v447, 2);
}

_v434 _v890(_v428 _v563) {
    return _v889(_v568(_v563));
}

bkr_i64 _v891(bkr_i64 _v447) {
    return _v505(_v447, 1);
}

bkr_i64 _v892(_v341 _v452) {
    return _v891(_v453(_v452));
}

bkr_i64 _v893(bkr_i64 _v447) {
    return _v894(_v447);
}

bkr_i64 _v894(bkr_i64 _v447) {
    return _v505(_v447, 2);
}

bkr_i64 _v895(_v341 _v452) {
    return _v894(_v453(_v452));
}

_v346 _v896(_v341 _v452) {
    return _v517(_v895(_v452));
}

bkr_i64 _v897(bkr_i64 _v447) {
    return _v609(_v898(_v447));
}

_v434 _v898(bkr_i64 _v447) {
    return _v646(_v447, 2);
}

_v434 _v899(_v341 _v452) {
    return _v898(_v453(_v452));
}

bkr_i64 _v900(bkr_i64 _v447) {
    return _v505(_v447, 3);
}

bkr_i64 _v901(_v341 _v452) {
    return _v900(_v453(_v452));
}

bkr_i64 _v902(bkr_i64 _v447) {
    return _v627(_v903(_v447));
}

bkr_i64 _v904(_v341 _v452) {
    return _v902(_v453(_v452));
}

_v437 _v903(bkr_i64 _v447) {
    return _v652(_v447, 4);
}

_v437 _v905(_v341 _v452) {
    return _v903(_v453(_v452));
}

bkr_i64 _v906(bkr_i64 _v606) {
    return _v907(_v605(_v606));
}

bkr_i64 _v907(_v434 _v608) {
    return vec_len(_v609(_v608));
}

bkr_i64 _v908(bkr_i64 _v606, bkr_i64 _v362) {
    return _v909(_v605(_v606), _v362);
}

bkr_i64 _v909(_v434 _v608, bkr_i64 _v362) {
    return _v509(_v910(_v608, _v362));
}

bkr_i64 _v911(bkr_i64 _v606, bkr_i64 _v362) {
    return _v910(_v605(_v606), _v362);
}

bkr_i64 _v910(_v434 _v608, bkr_i64 _v362) {
    return vec_get(_v609(_v608), _v362);
}

_v341 _v912(bkr_i64 _v606, bkr_i64 _v362) {
    return _v913(_v605(_v606), _v362);
}

_v341 _v913(_v434 _v608, bkr_i64 _v362) {
    return _v507(_v910(_v608, _v362));
}

_v428 _v914(_v434 _v608, bkr_i64 _v362) {
    return _v559(_v910(_v608, _v362));
}

bkr_i64 _v915(bkr_i64 _v613) {
    return _v916(_v612(_v613));
}

bkr_i64 _v916(_v435 _v615) {
    return vec_len(_v616(_v615));
}

bkr_i64 _v917(bkr_i64 _v613, bkr_i64 _v362) {
    return _v918(_v612(_v613), _v362);
}

bkr_i64 _v918(_v435 _v615, bkr_i64 _v362) {
    return vec_get(_v616(_v615), _v362);
}

bkr_i64 _v919(bkr_i64 _v406) {
    return _v920(_v619(_v406));
}

bkr_i64 _v920(_v436 _v621) {
    return vec_len(_v622(_v621));
}

bkr_i64 _v921(bkr_i64 _v406, bkr_i64 _v362) {
    return _v922(_v619(_v406), _v362);
}

bkr_i64 _v922(_v436 _v621, bkr_i64 _v362) {
    return _v595(_v923(_v621, _v362));
}

bkr_i64 _v923(_v436 _v621, bkr_i64 _v362) {
    return vec_get(_v622(_v621), _v362);
}

_v433 _v924(bkr_i64 _v406, bkr_i64 _v362) {
    return _v925(_v619(_v406), _v362);
}

_v433 _v925(_v436 _v621, bkr_i64 _v362) {
    return _v592(_v923(_v621, _v362));
}

bkr_i64 _v926(bkr_i64 _v0) {
    return _v907(_v898(_v0));
}

bkr_i64 _v927(bkr_i64 _v0, bkr_i64 _v362) {
    return _v909(_v898(_v0), _v362);
}

bkr_i64 _v928(bkr_i64 _v0, bkr_i64 _v362) {
    return _v910(_v898(_v0), _v362);
}

bkr_i64 _v929(bkr_i64 _v930) {
    return _v907(_v871(_v930));
}

bkr_i64 _v931(bkr_i64 _v930, bkr_i64 _v362) {
    return _v909(_v871(_v930), _v362);
}

bkr_i64 _v932(bkr_i64 _v933) {
    return _v907(_v889(_v933));
}

bkr_i64 _v934(bkr_i64 _v933, bkr_i64 _v362) {
    return _v909(_v889(_v933), _v362);
}

bkr_i64 _v935(bkr_i64 _v936) {
    return _v907(_v691(_v936));
}

bkr_i64 _v937(bkr_i64 _v936, bkr_i64 _v362) {
    return _v909(_v691(_v936), _v362);
}

bkr_i64 _v938(bkr_i64 _v936, bkr_i64 _v362) {
    return _v910(_v691(_v936), _v362);
}

bkr_i64 _v939(bkr_i64 _v940) {
    return _v907(_v701(_v940));
}

bkr_i64 _v941(bkr_i64 _v940, bkr_i64 _v362) {
    return _v909(_v701(_v940), _v362);
}

bkr_i64 _v942(bkr_i64 _v940, bkr_i64 _v362) {
    return _v910(_v701(_v940), _v362);
}

bkr_i64 _v943(bkr_i64 _v944) {
    return _v920(_v745(_v944));
}

bkr_i64 _v945(bkr_i64 _v944, bkr_i64 _v362) {
    return _v922(_v745(_v944), _v362);
}

bkr_i64 _v946(bkr_i64 _v944, bkr_i64 _v362) {
    return _v909(_v748(_v944), _v362);
}

bkr_i64 _v947(bkr_i64 _v944, bkr_i64 _v362) {
    return _v910(_v748(_v944), _v362);
}

bkr_i64 _v948(bkr_i64 _v447) {
    return _v916(_v727(_v447));
}

bkr_i64 _v949(bkr_i64 _v447, bkr_i64 _v362) {
    return _v918(_v727(_v447), _v362);
}

bkr_i64 _v950(bkr_i64 _v447, bkr_i64 _v362) {
    return _v909(_v730(_v447), _v362);
}

bkr_i64 _v951(bkr_i64 _v447, bkr_i64 _v362) {
    return _v910(_v730(_v447), _v362);
}

_v343 _v952(bkr_i64 _v319) {
    return (_v343){._v319 = _v319, ._v339 = _v268, ._v340 = _v268, ._v344 = 0, ._v345 = (-1)};
}

_v343 _v953(bkr_i64 _v954, bkr_i64 _v955) {
    return (_v343){._v319 = 6, ._v339 = _v268, ._v340 = _v268, ._v344 = _v954, ._v345 = _v955};
}

_v343 _v956(bkr_i64 _v355) {
    return (_v343){._v319 = 7, ._v339 = _v268, ._v340 = _v268, ._v344 = _v355, ._v345 = (-1)};
}

_v343 _v957(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345) {
    return (_v343){._v319 = _v319, ._v339 = _v268, ._v340 = _v268, ._v344 = _v344, ._v345 = _v345};
}

bkr_i64 _v958(_v343 _v959) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v226);
    vec_push(_v447, _v959._v339);
    vec_push(_v447, _v959._v340);
    vec_push(_v447, _v959._v319);
    if ((_v959._v319 == 6)) {
        vec_push(_v447, _v959._v344);
        vec_push(_v447, _v959._v345);
    }
    if ((_v959._v319 == 7)) {
        vec_push(_v447, _v959._v344);
    }
    if (((((_v959._v319 == 8) || (_v959._v319 == 9)) || (_v959._v319 == 10)) || (_v959._v319 == 11))) {
        vec_push(_v447, _v959._v344);
        vec_push(_v447, _v959._v345);
    }
    return _v447;
}

_v343 _v529(bkr_i64 _v447) {
    bkr_i64 _v319 = _v316;
    bkr_i64 _v344 = 0;
    bkr_i64 _v345 = (-1);
    if ((vec_len(_v447) > _v272)) {
        _v319 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v344 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v345 = vec_get(_v447, (_v272 + 2));
    }
    return (_v343){._v319 = _v319, ._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v344 = _v344, ._v345 = _v345};
}

_v346 _v960(bkr_i64 _v319) {
    _v343 _v531 = _v952(_v319);
    return _v517(((bkr_i64)(_v958(_v531))));
}

bkr_i64 _v961(bkr_i64 _v319) {
    return _v527(_v960(_v319));
}

_v346 _v962(bkr_i64 _v954, bkr_i64 _v955) {
    _v343 _v531 = _v953(_v954, _v955);
    return _v517(((bkr_i64)(_v958(_v531))));
}

bkr_i64 _v963(bkr_i64 _v954, bkr_i64 _v955) {
    return _v527(_v962(_v954, _v955));
}

_v346 _v964(bkr_i64 _v355) {
    _v343 _v531 = _v956(_v355);
    return _v517(((bkr_i64)(_v958(_v531))));
}

bkr_i64 _v965(bkr_i64 _v355) {
    return _v527(_v964(_v355));
}

_v346 _v966(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345) {
    _v343 _v531 = _v957(_v319, _v344, _v345);
    return _v517(((bkr_i64)(_v958(_v531))));
}

bkr_i64 _v967(bkr_i64 _v319, bkr_i64 _v344, bkr_i64 _v345) {
    return _v527(_v966(_v319, _v344, _v345));
}

bkr_i64 _v968(bkr_i64 _v319, bkr_i64 _v387) {
    return _v462(_v458(_v319, _v387));
}

bkr_i64 _v969(bkr_i64 _v463) {
    _v430 _v753 = _v464(_v463);
    return _v753._v339;
}

bkr_i64 _v970(bkr_i64 _v463) {
    _v430 _v753 = _v464(_v463);
    return _v753._v340;
}

bkr_i64 _v971(bkr_i64 _v463, bkr_i64 _v339, bkr_i64 _v340) {
    _v472(_v593(_v463), _v339, _v340);
    return _v463;
}

_v404 _v972(bkr_i64 _v405, bkr_i64 _v406, bkr_i64 _v407, bkr_i64 _v408) {
    return (_v404){._v339 = _v268, ._v340 = _v268, ._v405 = _v405, ._v406 = _v406, ._v407 = _v407, ._v408 = _v408};
}

bkr_i64 _v973(_v404 _v368) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v258);
    vec_push(_v447, _v368._v339);
    vec_push(_v447, _v368._v340);
    vec_push(_v447, _v368._v405);
    vec_push(_v447, _v368._v406);
    vec_push(_v447, _v368._v407);
    vec_push(_v447, _v368._v408);
    return _v447;
}

_v404 _v811(bkr_i64 _v447) {
    bkr_i64 _v405 = 0;
    bkr_i64 _v406 = 0;
    bkr_i64 _v407 = 0;
    bkr_i64 _v408 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v405 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v406 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v407 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v408 = vec_get(_v447, (_v272 + 3));
    }
    return (_v404){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v405 = _v405, ._v406 = _v406, ._v407 = _v407, ._v408 = _v408};
}

_v426 _v974(_v426 _v975, _v436 _v621, _v434 _v976, _v435 _v977) {
    _v404 _v531 = _v972(_v541(_v975), _v620(_v621), _v607(_v976), _v614(_v977));
    return _v538(((bkr_i64)(_v973(_v531))));
}

bkr_i64 _v978(bkr_i64 _v405, bkr_i64 _v406, bkr_i64 _v407) {
    bkr_i64 _v979 = vec_new();
    return _v544(_v974(_v539(_v405), _v619(_v406), _v605(_v407), _v612(_v979)));
}

_v347 _v980(bkr_i64 _v319, bkr_i64 _v344) {
    return (_v347){._v319 = _v319, ._v339 = _v268, ._v340 = _v268, ._v344 = _v344};
}

bkr_i64 _v981(_v347 _v982) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v982._v319);
    vec_push(_v447, _v982._v339);
    vec_push(_v447, _v982._v340);
    vec_push(_v447, _v982._v344);
    return _v447;
}

_v347 _v662(bkr_i64 _v447) {
    bkr_i64 _v344 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v344 = vec_get(_v447, _v272);
    }
    return (_v347){._v319 = vec_get(_v447, 0), ._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v344 = _v344};
}

_v426 _v983(bkr_i64 _v319, bkr_i64 _v344) {
    _v347 _v531 = _v980(_v319, _v344);
    return _v538(((bkr_i64)(_v981(_v531))));
}

_v426 _v984(bkr_i64 _v387) {
    return _v983(24, _v387);
}

bkr_i64 _v985(bkr_i64 _v387) {
    return _v544(_v984(_v387));
}

_v426 _v986(bkr_str _v387) {
    return _v983(29, ((bkr_i64)(_v387)));
}

bkr_i64 _v987(bkr_str _v387) {
    return _v544(_v986(_v387));
}

_v426 _v988(bkr_i64 _v387) {
    return _v983(25, _v387);
}

bkr_i64 _v989(bkr_i64 _v387) {
    return _v544(_v988(_v387));
}

_v426 _v990(bkr_str _v387) {
    return _v983(26, ((bkr_i64)(_v387)));
}

bkr_i64 _v991(bkr_str _v387) {
    return _v544(_v990(_v387));
}

_v395 _v992(bkr_i64 _v396) {
    return (_v395){._v339 = _v268, ._v340 = _v268, ._v396 = _v396};
}

bkr_i64 _v993(_v395 _v368) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v252);
    vec_push(_v447, _v368._v339);
    vec_push(_v447, _v368._v340);
    vec_push(_v447, _v368._v396);
    return _v447;
}

_v395 _v807(bkr_i64 _v447) {
    bkr_i64 _v396 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v396 = vec_get(_v447, _v272);
    }
    return (_v395){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v396 = _v396};
}

_v426 _v994(_v434 _v995) {
    _v395 _v531 = _v992(_v607(_v995));
    return _v538(((bkr_i64)(_v993(_v531))));
}

bkr_i64 _v996(bkr_i64 _v396) {
    return _v544(_v994(_v605(_v396)));
}

_v397 _v997(bkr_i64 _v398, bkr_i64 _v399) {
    return (_v397){._v339 = _v268, ._v340 = _v268, ._v398 = _v398, ._v399 = _v399};
}

bkr_i64 _v998(_v397 _v368) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v239);
    vec_push(_v447, _v368._v339);
    vec_push(_v447, _v368._v340);
    vec_push(_v447, _v368._v398);
    vec_push(_v447, _v368._v399);
    return _v447;
}

_v397 _v999(bkr_i64 _v447) {
    bkr_i64 _v398 = 0;
    bkr_i64 _v399 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v398 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v399 = vec_get(_v447, (_v272 + 1));
    }
    return (_v397){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v398 = _v398, ._v399 = _v399};
}

_v426 _v1000(_v426 _v1001, bkr_i64 _v399) {
    _v397 _v531 = _v997(_v541(_v1001), _v399);
    return _v538(((bkr_i64)(_v998(_v531))));
}

bkr_i64 _v1002(bkr_i64 _v398, bkr_i64 _v399) {
    return _v544(_v1000(_v539(_v398), _v399));
}

_v400 _v1003(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402) {
    return (_v400){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v401 = _v401, ._v402 = _v402, ._v403 = 0};
}

_v400 _v1004(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402, bkr_i64 _v403) {
    return (_v400){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v401 = _v401, ._v402 = _v402, ._v403 = _v403};
}

bkr_i64 _v1005(_v400 _v368) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v257);
    vec_push(_v447, _v368._v339);
    vec_push(_v447, _v368._v340);
    vec_push(_v447, _v368._v355);
    vec_push(_v447, _v368._v401);
    vec_push(_v447, _v368._v402);
    vec_push(_v447, _v368._v403);
    return _v447;
}

_v400 _v809(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v401 = 0;
    bkr_i64 _v402 = 0;
    bkr_i64 _v403 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v401 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v402 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v403 = vec_get(_v447, (_v272 + 3));
    }
    return (_v400){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v401 = _v401, ._v402 = _v402, ._v403 = _v403};
}

bkr_i64 _v1006(_v426 _v542) {
    bkr_i64 _v447 = _v544(_v542);
    if ((vec_len(_v447) > (_v272 + 3))) {
        return vec_get(_v447, (_v272 + 3));
    }
    return 0;
}

_v426 _v1007(bkr_i64 _v355, _v435 _v1008, _v434 _v1009, bkr_i64 _v403) {
    _v400 _v531 = _v1004(_v355, _v614(_v1008), _v607(_v1009), _v403);
    return _v538(((bkr_i64)(_v1005(_v531))));
}

_v426 _v1010(bkr_i64 _v355, _v435 _v1008, _v434 _v1009) {
    _v400 _v531 = _v1003(_v355, _v614(_v1008), _v607(_v1009));
    return _v538(((bkr_i64)(_v1005(_v531))));
}

bkr_i64 _v1011(bkr_i64 _v355, bkr_i64 _v401, bkr_i64 _v402) {
    return _v544(_v1010(_v355, _v612(_v401), _v605(_v402)));
}

_v354 _v1012(bkr_i64 _v355, bkr_i64 _v356) {
    return (_v354){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v356 = _v356};
}

bkr_i64 _v1013(_v354 _v1014) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v244);
    vec_push(_v447, _v1014._v339);
    vec_push(_v447, _v1014._v340);
    vec_push(_v447, _v1014._v355);
    vec_push(_v447, _v1014._v356);
    return _v447;
}

_v354 _v688(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v356 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v356 = vec_get(_v447, (_v272 + 1));
    }
    return (_v354){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v356 = _v356};
}

_v426 _v1015(bkr_i64 _v355, _v434 _v1016) {
    _v354 _v531 = _v1012(_v355, _v607(_v1016));
    return _v538(((bkr_i64)(_v1013(_v531))));
}

bkr_i64 _v1017(bkr_i64 _v355, bkr_i64 _v356) {
    return _v544(_v1015(_v355, _v605(_v356)));
}

_v357 _v1018(bkr_i64 _v358, bkr_i64 _v359, bkr_i64 _v356) {
    return (_v357){._v339 = _v268, ._v340 = _v268, ._v358 = _v358, ._v359 = _v359, ._v356 = _v356};
}

bkr_i64 _v1019(_v357 _v1014) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v261);
    vec_push(_v447, _v1014._v339);
    vec_push(_v447, _v1014._v340);
    vec_push(_v447, _v1014._v358);
    vec_push(_v447, _v1014._v359);
    vec_push(_v447, _v1014._v356);
    return _v447;
}

_v357 _v1020(bkr_i64 _v447) {
    bkr_i64 _v358 = 0;
    bkr_i64 _v359 = 0;
    bkr_i64 _v356 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v358 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v359 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v356 = vec_get(_v447, (_v272 + 2));
    }
    return (_v357){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v358 = _v358, ._v359 = _v359, ._v356 = _v356};
}

_v426 _v1021(_v426 _v1022, bkr_i64 _v359, _v434 _v1016) {
    _v357 _v531 = _v1018(_v541(_v1022), _v359, _v607(_v1016));
    return _v538(((bkr_i64)(_v1019(_v531))));
}

bkr_i64 _v1023(bkr_i64 _v358, bkr_i64 _v359, bkr_i64 _v356) {
    return _v544(_v1021(_v539(_v358), _v359, _v605(_v356)));
}

_v426 _v1024(bkr_i64 _v355) {
    return _v983(23, _v355);
}

bkr_i64 _v1025(_v426 _v1026) {
    return _v663(_v1026);
}

bkr_i64 _v1027(bkr_i64 _v355) {
    return _v544(_v1024(_v355));
}

_v352 _v1028(bkr_i64 _v349, bkr_i64 _v353) {
    return (_v352){._v339 = _v268, ._v340 = _v268, ._v349 = _v349, ._v353 = _v353};
}

bkr_i64 _v1029(_v352 _v1030) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v243);
    vec_push(_v447, _v1030._v339);
    vec_push(_v447, _v1030._v340);
    vec_push(_v447, _v1030._v349);
    vec_push(_v447, _v1030._v353);
    return _v447;
}

_v352 _v681(bkr_i64 _v447) {
    bkr_i64 _v349 = 0;
    bkr_i64 _v353 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v349 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v353 = vec_get(_v447, (_v272 + 1));
    }
    return (_v352){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v349 = _v349, ._v353 = _v353};
}

_v426 _v1031(bkr_i64 _v349, _v426 _v1032) {
    _v352 _v531 = _v1028(_v349, _v541(_v1032));
    return _v538(((bkr_i64)(_v1029(_v531))));
}

bkr_i64 _v1033(bkr_i64 _v349, bkr_i64 _v353) {
    return _v544(_v1031(_v349, _v539(_v353)));
}

_v360 _v1034(bkr_i64 _v361, bkr_i64 _v362) {
    return (_v360){._v339 = _v268, ._v340 = _v268, ._v361 = _v361, ._v362 = _v362};
}

bkr_i64 _v1035(_v360 _v1036) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v253);
    vec_push(_v447, _v1036._v339);
    vec_push(_v447, _v1036._v340);
    vec_push(_v447, _v1036._v361);
    vec_push(_v447, _v1036._v362);
    return _v447;
}

_v360 _v711(bkr_i64 _v447) {
    bkr_i64 _v361 = 0;
    bkr_i64 _v362 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v361 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v362 = vec_get(_v447, (_v272 + 1));
    }
    return (_v360){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v361 = _v361, ._v362 = _v362};
}

_v426 _v1037(_v426 _v1038, _v426 _v1039) {
    _v360 _v531 = _v1034(_v541(_v1038), _v541(_v1039));
    return _v538(((bkr_i64)(_v1035(_v531))));
}

bkr_i64 _v1040(bkr_i64 _v361, bkr_i64 _v362) {
    return _v544(_v1037(_v539(_v361), _v539(_v362)));
}

_v363 _v1041(bkr_i64 _v361, bkr_i64 _v355) {
    return (_v363){._v339 = _v268, ._v340 = _v268, ._v361 = _v361, ._v355 = _v355};
}

bkr_i64 _v1042(_v363 _v1043) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v256);
    vec_push(_v447, _v1043._v339);
    vec_push(_v447, _v1043._v340);
    vec_push(_v447, _v1043._v361);
    vec_push(_v447, _v1043._v355);
    return _v447;
}

_v363 _v719(bkr_i64 _v447) {
    bkr_i64 _v361 = 0;
    bkr_i64 _v355 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v361 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v355 = vec_get(_v447, (_v272 + 1));
    }
    return (_v363){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v361 = _v361, ._v355 = _v355};
}

_v426 _v1044(_v426 _v1038, bkr_i64 _v1045) {
    _v363 _v531 = _v1041(_v541(_v1038), _v1045);
    return _v538(((bkr_i64)(_v1042(_v531))));
}

bkr_i64 _v1046(bkr_i64 _v361, bkr_i64 _v1045) {
    return _v544(_v1044(_v539(_v361), _v1045));
}

_v348 _v1047(bkr_i64 _v349, bkr_i64 _v350, bkr_i64 _v351) {
    return (_v348){._v339 = _v268, ._v340 = _v268, ._v349 = _v349, ._v350 = _v350, ._v351 = _v351};
}

bkr_i64 _v1048(_v348 _v1049) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v242);
    vec_push(_v447, _v1049._v339);
    vec_push(_v447, _v1049._v340);
    vec_push(_v447, _v1049._v349);
    vec_push(_v447, _v1049._v350);
    vec_push(_v447, _v1049._v351);
    return _v447;
}

_v348 _v671(bkr_i64 _v447) {
    bkr_i64 _v349 = 0;
    bkr_i64 _v350 = 0;
    bkr_i64 _v351 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v349 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v350 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v351 = vec_get(_v447, (_v272 + 2));
    }
    return (_v348){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v349 = _v349, ._v350 = _v350, ._v351 = _v351};
}

_v426 _v1050(bkr_i64 _v349, _v426 _v1051, _v426 _v1052) {
    _v348 _v531 = _v1047(_v349, _v541(_v1051), _v541(_v1052));
    return _v538(((bkr_i64)(_v1048(_v531))));
}

bkr_i64 _v1053(bkr_i64 _v349, bkr_i64 _v350, bkr_i64 _v351) {
    return _v544(_v1050(_v349, _v539(_v350), _v539(_v351)));
}

_v392 _v1054(bkr_i64 _v375, bkr_i64 _v393, bkr_i64 _v394) {
    return (_v392){._v339 = _v268, ._v340 = _v268, ._v375 = _v375, ._v393 = _v393, ._v394 = _v394};
}

bkr_i64 _v1055(_v392 _v368) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v250);
    vec_push(_v447, _v368._v339);
    vec_push(_v447, _v368._v340);
    vec_push(_v447, _v368._v375);
    vec_push(_v447, _v368._v393);
    vec_push(_v447, _v368._v394);
    return _v447;
}

_v392 _v805(bkr_i64 _v447) {
    bkr_i64 _v375 = 0;
    bkr_i64 _v393 = 0;
    bkr_i64 _v394 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v375 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v393 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v394 = vec_get(_v447, (_v272 + 2));
    }
    return (_v392){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v375 = _v375, ._v393 = _v393, ._v394 = _v394};
}

_v426 _v1056(_v426 _v1057, _v426 _v1058, _v426 _v1059) {
    _v392 _v531 = _v1054(_v541(_v1057), _v541(_v1058), _v541(_v1059));
    return _v538(((bkr_i64)(_v1055(_v531))));
}

bkr_i64 _v1060(bkr_i64 _v375, bkr_i64 _v393, bkr_i64 _v394) {
    return _v544(_v1056(_v539(_v375), _v539(_v393), _v539(_v394)));
}

_v364 _v1061(bkr_i64 _v355, bkr_i64 _v365, bkr_i64 _v366) {
    return (_v364){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v365 = _v365, ._v366 = _v366};
}

bkr_i64 _v1062(_v364 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v228);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v355);
    vec_push(_v447, _v370._v365);
    vec_push(_v447, _v370._v366);
    return _v447;
}

_v364 _v757(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v365 = 0;
    bkr_i64 _v366 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v365 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v366 = vec_get(_v447, (_v272 + 2));
    }
    return (_v364){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v365 = _v365, ._v366 = _v366};
}

_v427 _v1063(bkr_i64 _v355, bkr_i64 _v516, bkr_i64 _v366) {
    _v364 _v531 = _v1061(_v355, _v516, _v366);
    return _v550(((bkr_i64)(_v1062(_v531))));
}

_v427 _v1064(_v427 _v554) {
    bkr_i64 _v447 = _v555(_v554);
    while ((vec_len(_v447) < (_v272 + 3))) {
        vec_push(_v447, 0);
    }
    vec_push(_v447, 1);
    return _v554;
}

bkr_bool _v1066(_v427 _v554) {
    bkr_i64 _v447 = _v555(_v554);
    return ((vec_len(_v447) > (_v272 + 3)) && (vec_get(_v447, (_v272 + 3)) == 1));
}

bkr_i64 _v1067(bkr_i64 _v355, bkr_i64 _v516, bkr_i64 _v366) {
    return _v555(_v1063(_v355, _v516, _v366));
}

_v367 _v1068(bkr_i64 _v368) {
    return (_v367){._v339 = _v268, ._v340 = _v268, ._v368 = _v368};
}

bkr_i64 _v1069(_v367 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v229);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v368);
    return _v447;
}

_v367 _v768(bkr_i64 _v447) {
    bkr_i64 _v368 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v368 = vec_get(_v447, _v272);
    }
    return (_v367){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v368 = _v368};
}

_v427 _v1070(bkr_i64 _v368) {
    _v367 _v531 = _v1068(_v368);
    return _v550(((bkr_i64)(_v1069(_v531))));
}

bkr_i64 _v1071(bkr_i64 _v368) {
    return _v555(_v1070(_v368));
}

_v369 _v1072(bkr_i64 _v370) {
    return (_v369){._v339 = _v268, ._v340 = _v268, ._v370 = _v370};
}

bkr_i64 _v1073(_v369 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v238);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v370);
    return _v447;
}

_v369 _v772(bkr_i64 _v447) {
    bkr_i64 _v370 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v370 = vec_get(_v447, _v272);
    }
    return (_v369){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v370 = _v370};
}

_v427 _v1074(_v427 _v370) {
    _v369 _v531 = _v1072(_v553(_v370));
    return _v550(((bkr_i64)(_v1073(_v531))));
}

bkr_i64 _v1075(bkr_i64 _v370) {
    return _v555(_v1074(_v551(_v370)));
}

_v371 _v1076(bkr_i64 _v368) {
    return (_v371){._v339 = _v268, ._v340 = _v268, ._v368 = _v368};
}

bkr_i64 _v1077(_v371 _v1078) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v240);
    vec_push(_v447, _v1078._v339);
    vec_push(_v447, _v1078._v340);
    vec_push(_v447, _v1078._v368);
    return _v447;
}

_v371 _v777(bkr_i64 _v447) {
    bkr_i64 _v368 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v368 = vec_get(_v447, _v272);
    }
    return (_v371){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v368 = _v368};
}

_v426 _v1079(_v426 _v368) {
    _v371 _v531 = _v1076(_v541(_v368));
    return _v538(((bkr_i64)(_v1077(_v531))));
}

bkr_i64 _v1080(bkr_i64 _v368) {
    return _v544(_v1079(_v539(_v368)));
}

_v372 _v1081(bkr_i64 _v368, bkr_i64 _v373) {
    return (_v372){._v339 = _v268, ._v340 = _v268, ._v368 = _v368, ._v373 = _v373};
}

bkr_i64 _v1082(_v372 _v1083) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v241);
    vec_push(_v447, _v1083._v339);
    vec_push(_v447, _v1083._v340);
    vec_push(_v447, _v1083._v368);
    vec_push(_v447, _v1083._v373);
    return _v447;
}

_v372 _v1084(bkr_i64 _v447) {
    bkr_i64 _v368 = 0;
    bkr_i64 _v373 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v368 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v373 = vec_get(_v447, (_v272 + 1));
    }
    return (_v372){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v368 = _v368, ._v373 = _v373};
}

_v426 _v1085(_v426 _v368, _v346 _v373) {
    _v372 _v531 = _v1081(_v541(_v368), _v520(_v373));
    return _v538(((bkr_i64)(_v1082(_v531))));
}

bkr_i64 _v1086(bkr_i64 _v368, bkr_i64 _v373) {
    return _v544(_v1085(_v539(_v368), _v518(_v373)));
}

_v389 _v1087(void) {
    return (_v389){._v339 = _v268, ._v340 = _v268};
}

bkr_i64 _v1088(_v389 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v234);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    return _v447;
}

_v389 _v799(bkr_i64 _v447) {
    return (_v389){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270)};
}

_v427 _v1089(void) {
    _v389 _v531 = _v1087();
    return _v550(((bkr_i64)(_v1088(_v531))));
}

bkr_i64 _v1090(void) {
    return _v555(_v1089());
}

_v390 _v1091(void) {
    return (_v390){._v339 = _v268, ._v340 = _v268};
}

bkr_i64 _v1092(_v390 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v235);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    return _v447;
}

_v390 _v801(bkr_i64 _v447) {
    return (_v390){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270)};
}

_v427 _v1093(void) {
    _v390 _v531 = _v1091();
    return _v550(((bkr_i64)(_v1092(_v531))));
}

bkr_i64 _v1094(void) {
    return _v555(_v1093());
}

_v385 _v1095(bkr_i64 _v386, bkr_i64 _v387) {
    return (_v385){._v339 = _v268, ._v340 = _v268, ._v386 = _v386, ._v387 = _v387};
}

bkr_i64 _v1096(_v385 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v233);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v386);
    vec_push(_v447, _v370._v387);
    return _v447;
}

_v385 _v795(bkr_i64 _v447) {
    bkr_i64 _v386 = 0;
    bkr_i64 _v387 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v386 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v387 = vec_get(_v447, (_v272 + 1));
    }
    return (_v385){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v386 = _v386, ._v387 = _v387};
}

_v427 _v1097(_v426 _v1098, _v426 _v1099) {
    _v385 _v531 = _v1095(_v541(_v1098), _v541(_v1099));
    return _v550(((bkr_i64)(_v1096(_v531))));
}

bkr_i64 _v1100(bkr_i64 _v386, bkr_i64 _v387) {
    return _v555(_v1097(_v539(_v386), _v539(_v387)));
}

_v388 _v1101(bkr_i64 _v368) {
    return (_v388){._v339 = _v268, ._v340 = _v268, ._v368 = _v368};
}

bkr_i64 _v1102(_v388 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v232);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v368);
    return _v447;
}

_v388 _v797(bkr_i64 _v447) {
    bkr_i64 _v368 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v368 = vec_get(_v447, _v272);
    }
    return (_v388){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v368 = _v368};
}

_v427 _v1103(_v426 _v542) {
    _v388 _v531 = _v1101(_v541(_v542));
    return _v550(((bkr_i64)(_v1102(_v531))));
}

bkr_i64 _v1104(bkr_i64 _v368) {
    return _v555(_v1103(_v539(_v368)));
}

_v391 _v1105(void) {
    return (_v391){._v339 = _v268, ._v340 = _v268};
}

bkr_i64 _v1106(_v391 _v578) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v227);
    vec_push(_v447, _v578._v339);
    vec_push(_v447, _v578._v340);
    return _v447;
}

_v391 _v803(bkr_i64 _v447) {
    return (_v391){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270)};
}

_v429 _v1107(void) {
    _v391 _v531 = _v1105();
    return _v579(((bkr_i64)(_v1106(_v531))));
}

bkr_i64 _v1108(void) {
    return _v585(_v1107());
}

bkr_i64 _v1109(bkr_i64 _v578) {
    return _v590(_v580(_v578));
}

bkr_i64 _v1110(bkr_i64 _v578, bkr_i64 _v362) {
    return _v509(vec_get(_v578, (_v272 + _v362)));
}

_v427 _v1111(_v429 _v583, bkr_i64 _v362) {
    return _v551(_v1110(_v585(_v583), _v362));
}

bkr_i64 _v1112(bkr_i64 _v578) {
    return _v1110(_v578, (_v1109(_v578) - 1));
}

_v429 _v1113(_v429 _v583, _v427 _v554) {
    _v451(_v507(_v582(_v583)), _v553(_v554));
    return _v583;
}

bkr_i64 _v1114(bkr_i64 _v578, bkr_i64 _v370) {
    _v1113(_v580(_v578), _v551(_v370));
    return _v578;
}

_v429 _v1115(_v427 _v554) {
    bkr_i64 _v370 = _v555(_v554);
    _v429 _v583 = _v1107();
    _v454(_v507(_v582(_v583)), _v485(_v370), _v486(_v370));
    _v1113(_v583, _v554);
    return _v583;
}

bkr_i64 _v1116(bkr_i64 _v370) {
    return _v585(_v1115(_v551(_v370)));
}

_v374 _v1117(bkr_i64 _v375, bkr_i64 _v376, bkr_i64 _v377) {
    return (_v374){._v339 = _v268, ._v340 = _v268, ._v375 = _v375, ._v376 = _v376, ._v377 = _v377};
}

bkr_i64 _v1118(_v374 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v230);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v375);
    vec_push(_v447, _v370._v376);
    vec_push(_v447, _v370._v377);
    return _v447;
}

_v374 _v787(bkr_i64 _v447) {
    bkr_i64 _v375 = 0;
    bkr_i64 _v376 = 0;
    bkr_i64 _v377 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v375 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v376 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v377 = vec_get(_v447, (_v272 + 2));
    }
    return (_v374){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v375 = _v375, ._v376 = _v376, ._v377 = _v377};
}

_v427 _v1119(_v426 _v1057, _v429 _v1120, bkr_i64 _v377) {
    _v374 _v531 = _v1117(_v541(_v1057), _v582(_v1120), _v377);
    return _v550(((bkr_i64)(_v1118(_v531))));
}

bkr_i64 _v1121(bkr_i64 _v375, bkr_i64 _v376, bkr_i64 _v377) {
    return _v555(_v1119(_v539(_v375), _v580(_v376), _v377));
}

_v380 _v1122(bkr_i64 _v355, bkr_i64 _v381, bkr_i64 _v382, bkr_i64 _v383, bkr_i64 _v379) {
    return (_v380){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v381 = _v381, ._v382 = _v382, ._v383 = _v383, ._v379 = _v379};
}

bkr_i64 _v1123(_v380 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v236);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v355);
    vec_push(_v447, _v370._v381);
    vec_push(_v447, _v370._v382);
    vec_push(_v447, _v370._v383);
    vec_push(_v447, _v370._v379);
    return _v447;
}

_v380 _v791(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v381 = 0;
    bkr_i64 _v382 = 0;
    bkr_i64 _v383 = 0;
    bkr_i64 _v379 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v381 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v382 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v383 = vec_get(_v447, (_v272 + 3));
    }
    if ((vec_len(_v447) > (_v272 + 4))) {
        _v379 = vec_get(_v447, (_v272 + 4));
    }
    return (_v380){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v381 = _v381, ._v382 = _v382, ._v383 = _v383, ._v379 = _v379};
}

_v427 _v1124(bkr_i64 _v355, _v426 _v1125, _v426 _v1126, bkr_i64 _v383, _v429 _v1127) {
    _v380 _v531 = _v1122(_v355, _v541(_v1125), _v541(_v1126), _v383, _v582(_v1127));
    return _v550(((bkr_i64)(_v1123(_v531))));
}

bkr_i64 _v1128(bkr_i64 _v355, bkr_i64 _v381, bkr_i64 _v382, bkr_i64 _v383, bkr_i64 _v379) {
    return _v555(_v1124(_v355, _v539(_v381), _v539(_v382), _v383, _v580(_v379)));
}

_v378 _v1129(bkr_i64 _v375, bkr_i64 _v379) {
    return (_v378){._v339 = _v268, ._v340 = _v268, ._v375 = _v375, ._v379 = _v379};
}

bkr_i64 _v1130(_v378 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v231);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v375);
    vec_push(_v447, _v370._v379);
    return _v447;
}

_v378 _v789(bkr_i64 _v447) {
    bkr_i64 _v375 = 0;
    bkr_i64 _v379 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v375 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v379 = vec_get(_v447, (_v272 + 1));
    }
    return (_v378){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v375 = _v375, ._v379 = _v379};
}

_v427 _v1131(_v426 _v1057, _v429 _v1127) {
    _v378 _v531 = _v1129(_v541(_v1057), _v582(_v1127));
    return _v550(((bkr_i64)(_v1130(_v531))));
}

bkr_i64 _v1132(bkr_i64 _v375, bkr_i64 _v379) {
    return _v555(_v1131(_v539(_v375), _v580(_v379)));
}

_v384 _v1133(bkr_i64 _v379) {
    return (_v384){._v339 = _v268, ._v340 = _v268, ._v379 = _v379};
}

bkr_i64 _v1134(_v384 _v370) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v237);
    vec_push(_v447, _v370._v339);
    vec_push(_v447, _v370._v340);
    vec_push(_v447, _v370._v379);
    return _v447;
}

_v384 _v793(bkr_i64 _v447) {
    bkr_i64 _v379 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v379 = vec_get(_v447, _v272);
    }
    return (_v384){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v379 = _v379};
}

_v427 _v1135(_v429 _v1127) {
    _v384 _v531 = _v1133(_v582(_v1127));
    return _v550(((bkr_i64)(_v1134(_v531))));
}

bkr_i64 _v1136(bkr_i64 _v379) {
    return _v555(_v1135(_v580(_v379)));
}

_v409 _v1137(bkr_i64 _v355, bkr_i64 _v365) {
    return (_v409){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v365 = _v365};
}

bkr_i64 _v1138(_v409 _v1139) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v225);
    vec_push(_v447, _v1139._v339);
    vec_push(_v447, _v1139._v340);
    vec_push(_v447, _v1139._v355);
    vec_push(_v447, _v1139._v365);
    return _v447;
}

_v409 _v813(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v365 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v365 = vec_get(_v447, (_v272 + 1));
    }
    return (_v409){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v365 = _v365};
}

_v341 _v1140(bkr_i64 _v355, _v346 _v521) {
    _v409 _v531 = _v1137(_v355, _v520(_v521));
    return _v507(((bkr_i64)(_v1138(_v531))));
}

bkr_i64 _v1141(bkr_i64 _v355, bkr_i64 _v516) {
    return _v453(_v1140(_v355, _v518(_v516)));
}

_v410 _v1142(bkr_i64 _v355, bkr_i64 _v411, bkr_i64 _v412, bkr_i64 _v379) {
    return (_v410){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v411 = _v411, ._v412 = _v412, ._v379 = _v379};
}

bkr_i64 _v1143(_v410 _v558) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v224);
    vec_push(_v447, _v558._v339);
    vec_push(_v447, _v558._v340);
    vec_push(_v447, _v558._v355);
    vec_push(_v447, _v558._v411);
    vec_push(_v447, _v558._v412);
    vec_push(_v447, _v558._v379);
    return _v447;
}

_v410 _v815(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v411 = 0;
    bkr_i64 _v412 = 0;
    bkr_i64 _v379 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v411 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v412 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v379 = vec_get(_v447, (_v272 + 3));
    }
    return (_v410){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v411 = _v411, ._v412 = _v412, ._v379 = _v379};
}

_v428 _v1144(bkr_i64 _v355, _v434 _v1145, bkr_i64 _v1146, _v429 _v1127) {
    _v410 _v531 = _v1142(_v355, _v607(_v1145), _v1146, _v582(_v1127));
    return _v559(((bkr_i64)(_v1143(_v531))));
}

bkr_i64 _v1147(bkr_i64 _v355, bkr_i64 _v411, bkr_i64 _v1146, bkr_i64 _v379) {
    return _v568(_v1144(_v355, _v605(_v411), _v1146, _v580(_v379)));
}

_v413 _v1148(bkr_i64 _v355, bkr_i64 _v365, bkr_i64 _v387) {
    return (_v413){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v365 = _v365, ._v387 = _v387};
}

bkr_i64 _v1149(_v413 _v558) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v249);
    vec_push(_v447, _v558._v339);
    vec_push(_v447, _v558._v340);
    vec_push(_v447, _v558._v355);
    vec_push(_v447, _v558._v365);
    vec_push(_v447, _v558._v387);
    return _v447;
}

_v413 _v817(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v365 = 0;
    bkr_i64 _v387 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v365 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v387 = vec_get(_v447, (_v272 + 2));
    }
    return (_v413){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v365 = _v365, ._v387 = _v387};
}

_v428 _v1150(bkr_i64 _v355, bkr_i64 _v516, bkr_i64 _v387) {
    _v413 _v531 = _v1148(_v355, _v516, _v387);
    return _v559(((bkr_i64)(_v1149(_v531))));
}

bkr_i64 _v1151(bkr_i64 _v355, bkr_i64 _v516, bkr_i64 _v387) {
    return _v568(_v1150(_v355, _v516, _v387));
}

_v414 _v1152(bkr_i64 _v355, bkr_i64 _v365) {
    return (_v414){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v365 = _v365};
}

bkr_i64 _v1153(_v414 _v1154) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v255);
    vec_push(_v447, _v1154._v339);
    vec_push(_v447, _v1154._v340);
    vec_push(_v447, _v1154._v355);
    vec_push(_v447, _v1154._v365);
    return _v447;
}

_v414 _v819(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v365 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v365 = vec_get(_v447, (_v272 + 1));
    }
    return (_v414){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v365 = _v365};
}

_v341 _v1155(bkr_i64 _v1045, _v346 _v1156) {
    _v414 _v531 = _v1152(_v1045, _v520(_v1156));
    return _v507(((bkr_i64)(_v1153(_v531))));
}

bkr_i64 _v1157(bkr_i64 _v1045, bkr_i64 _v1158) {
    return _v453(_v1155(_v1045, _v518(_v1158)));
}

_v415 _v1159(bkr_i64 _v355, bkr_i64 _v416) {
    return (_v415){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v416 = _v416};
}

bkr_i64 _v1160(_v415 _v558) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v254);
    vec_push(_v447, _v558._v339);
    vec_push(_v447, _v558._v340);
    vec_push(_v447, _v558._v355);
    vec_push(_v447, _v558._v416);
    return _v447;
}

_v415 _v821(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v416 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v416 = vec_get(_v447, (_v272 + 1));
    }
    return (_v415){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v416 = _v416};
}

_v428 _v1161(bkr_i64 _v355, _v434 _v1162) {
    _v415 _v531 = _v1159(_v355, _v607(_v1162));
    return _v559(((bkr_i64)(_v1160(_v531))));
}

_v417 _v1163(bkr_i64 _v355, bkr_i64 _v418, bkr_i64 _v419) {
    return (_v417){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v418 = _v418, ._v419 = _v419};
}

bkr_i64 _v1164(_v417 _v558) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v259);
    vec_push(_v447, _v558._v339);
    vec_push(_v447, _v558._v340);
    vec_push(_v447, _v558._v355);
    vec_push(_v447, _v558._v418);
    vec_push(_v447, _v558._v419);
    return _v447;
}

_v417 _v823(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v418 = 0;
    bkr_i64 _v419 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v418 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v419 = vec_get(_v447, (_v272 + 2));
    }
    return (_v417){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v418 = _v418, ._v419 = _v419};
}

_v428 _v1165(bkr_i64 _v355, _v435 _v1166, _v435 _v1167) {
    _v417 _v531 = _v1163(_v355, _v614(_v1166), _v614(_v1167));
    return _v559(((bkr_i64)(_v1164(_v531))));
}

bkr_i64 _v1168(_v428 _v563) {
    return _v505(_v568(_v563), 1);
}

_v435 _v1169(_v428 _v563) {
    return _v648(_v568(_v563), 2);
}

_v435 _v1170(_v428 _v563) {
    return _v648(_v568(_v563), 3);
}

bkr_i64 _v1171(_v428 _v563) {
    _v435 _v1167 = _v1170(_v563);
    bkr_i64 _v399 = 0;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v916(_v1167))) {
        if (_v526(_v918(_v1167, _v1172))) {
            _v399 = (_v399 + 1);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v399;
}

bkr_i64 _v1173(_v428 _v563) {
    _v435 _v1167 = _v1170(_v563);
    bkr_i64 _v1174 = 0;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v916(_v1167))) {
        bkr_i64 _v344 = _v918(_v1167, _v1172);
        if (_v526(_v344)) {
            _v1174 = (_v1174 + _v916(_v611(_v344)));
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1174;
}

_v420 _v1175(bkr_i64 _v355, bkr_i64 _v421) {
    return (_v420){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v421 = _v421};
}

bkr_i64 _v1176(_v420 _v558) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v260);
    vec_push(_v447, _v558._v339);
    vec_push(_v447, _v558._v340);
    vec_push(_v447, _v558._v355);
    vec_push(_v447, _v558._v421);
    return _v447;
}

_v420 _v1177(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v421 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v421 = vec_get(_v447, (_v272 + 1));
    }
    return (_v420){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v421 = _v421};
}

_v428 _v1178(bkr_i64 _v355, _v346 _v1098) {
    _v420 _v531 = _v1175(_v355, _v520(_v1098));
    return _v559(((bkr_i64)(_v1176(_v531))));
}

bkr_i64 _v1179(bkr_i64 _v355, bkr_i64 _v373) {
    return _v568(_v1178(_v355, _v518(_v373)));
}

bkr_i64 _v1180(_v428 _v563) {
    return _v505(_v568(_v563), 1);
}

bkr_i64 _v1181(_v428 _v563) {
    return _v505(_v568(_v563), 2);
}

bkr_i64 _v1182(bkr_i64 _v355, bkr_i64 _v416) {
    return _v568(_v1161(_v355, _v605(_v416)));
}

_v422 _v1183(bkr_i64 _v355, bkr_i64 _v423, bkr_i64 _v424, bkr_i64 _v425) {
    return (_v422){._v339 = _v268, ._v340 = _v268, ._v355 = _v355, ._v423 = _v423, ._v424 = _v424, ._v425 = _v425};
}

bkr_i64 _v1184(_v422 _v0) {
    bkr_i64 _v447 = vec_new();
    vec_push(_v447, _v223);
    vec_push(_v447, _v0._v339);
    vec_push(_v447, _v0._v340);
    vec_push(_v447, _v0._v355);
    vec_push(_v447, _v0._v423);
    vec_push(_v447, _v0._v424);
    vec_push(_v447, _v0._v425);
    return _v447;
}

_v422 _v825(bkr_i64 _v447) {
    bkr_i64 _v355 = 0;
    bkr_i64 _v423 = 0;
    bkr_i64 _v424 = 0;
    bkr_i64 _v425 = 0;
    if ((vec_len(_v447) > _v272)) {
        _v355 = vec_get(_v447, _v272);
    }
    if ((vec_len(_v447) > (_v272 + 1))) {
        _v423 = vec_get(_v447, (_v272 + 1));
    }
    if ((vec_len(_v447) > (_v272 + 2))) {
        _v424 = vec_get(_v447, (_v272 + 2));
    }
    if ((vec_len(_v447) > (_v272 + 3))) {
        _v425 = vec_get(_v447, (_v272 + 3));
    }
    return (_v422){._v339 = vec_get(_v447, _v269), ._v340 = vec_get(_v447, _v270), ._v355 = _v355, ._v423 = _v423, ._v424 = _v424, ._v425 = _v425};
}

_v341 _v1185(bkr_i64 _v355, _v434 _v1186, bkr_i64 _v1187, _v437 _v1188) {
    _v422 _v531 = _v1183(_v355, _v607(_v1186), _v1187, _v626(_v1188));
    return _v507(((bkr_i64)(_v1184(_v531))));
}

bkr_i64 _v1189(bkr_i64 _v355, bkr_i64 _v423, bkr_i64 _v1187, bkr_i64 _v425) {
    return _v453(_v1185(_v355, _v605(_v423), _v1187, _v625(_v425)));
}

bkr_i64 _v1191(bkr_i64 _v1192, bkr_i64 _v425, bkr_i64 _v613, bkr_i64 _v1193) {
    return _v1194(_v1195(_v1192, _v425, _v613, _v1193));
}

_v1190 _v1195(bkr_i64 _v1192, bkr_i64 _v425, bkr_i64 _v613, bkr_i64 _v1193) {
    bkr_i64 _v1196 = vec_new();
    vec_push(_v1196, ((bkr_i64)(_v1192)));
    vec_push(_v1196, ((bkr_i64)(_v425)));
    vec_push(_v1196, ((bkr_i64)(_v613)));
    vec_push(_v1196, ((bkr_i64)(_v1193)));
    return _v1197(_v1196);
}

_v1190 _v1197(bkr_i64 _v1196) {
    return (_v1190){._v342 = ((bkr_i64)(_v1196))};
}

bkr_i64 _v1194(_v1190 _v1198) {
    return ((bkr_i64)(_v1198._v342));
}

bkr_i64 _v1199(bkr_i64 _v1196) {
    return _v1200(_v1197(_v1196));
}

bkr_i64 _v1200(_v1190 _v1198) {
    return ((bkr_i64)(vec_get(_v1194(_v1198), 0)));
}

bkr_i64 _v1201(bkr_i64 _v1196) {
    return _v1202(_v1197(_v1196));
}

bkr_i64 _v1202(_v1190 _v1198) {
    return ((bkr_i64)(vec_get(_v1194(_v1198), 1)));
}

bkr_i64 _v1203(bkr_i64 _v1196) {
    return _v1204(_v1197(_v1196));
}

bkr_i64 _v1204(_v1190 _v1198) {
    return ((bkr_i64)(vec_get(_v1194(_v1198), 2)));
}

bkr_i64 _v1205(bkr_i64 _v1196) {
    return _v1206(_v1197(_v1196));
}

bkr_i64 _v1206(_v1190 _v1198) {
    return ((bkr_i64)(vec_get(_v1194(_v1198), 3)));
}

bkr_bool _v1207(bkr_i64 _v1208) {
    return ((((_v1208 >= 97) && (_v1208 <= 122)) || ((_v1208 >= 65) && (_v1208 <= 90))) || (_v1208 == 95));
}

bkr_bool _v1209(bkr_i64 _v1208) {
    return ((_v1208 >= 48) && (_v1208 <= 57));
}

bkr_bool _v1210(bkr_i64 _v1208) {
    return (_v1207(_v1208) || _v1209(_v1208));
}

bkr_i64 _v1211(bkr_str _v1212, bkr_i64 _v1213) {
    bkr_i64 _v1214 = bkr_len((bkr_str)(intptr_t)(_v1212));
    while ((_v1213 < _v1214)) {
        bkr_i64 _v1208 = char_code_at(_v1212, _v1213);
        if (((((_v1208 == 32) || (_v1208 == 9)) || (_v1208 == 10)) || (_v1208 == 13))) {
            _v1213 = (_v1213 + 1);
        } else {
            if (((_v1208 == 47) && ((_v1213 + 1) < _v1214))) {
                bkr_i64 _v1218 = char_code_at(_v1212, (_v1213 + 1));
                if ((_v1218 == 47)) {
                    _v1213 = (_v1213 + 2);
                    while (((_v1213 < _v1214) && (char_code_at(_v1212, _v1213) != 10))) {
                        _v1213 = (_v1213 + 1);
                    }
                } else {
                    return _v1213;
                }
            } else {
                return _v1213;
            }
        }
    }
    return _v1213;
}

bkr_i64 _v1219(bkr_i64 _v1208) {
    if (((_v1208 >= 48) && (_v1208 <= 57))) {
        return (_v1208 - 48);
    }
    if (((_v1208 >= 97) && (_v1208 <= 102))) {
        return (_v1208 - 87);
    }
    if (((_v1208 >= 65) && (_v1208 <= 70))) {
        return (_v1208 - 55);
    }
    return (-1);
}

bkr_i64 _v1220(bkr_str _v1212, bkr_i64 _v1213, bkr_i64 _v1221) {
    vec_set(_v1221, 0, 2);
    bkr_i64 _v1222 = char_code_at(_v1212, (_v1213 + 1));
    if ((_v1222 == 110)) {
        return 10;
    }
    if ((_v1222 == 116)) {
        return 9;
    }
    if ((_v1222 == 114)) {
        return 13;
    }
    if ((_v1222 == 48)) {
        return 0;
    }
    if ((_v1222 == 92)) {
        return 92;
    }
    if ((_v1222 == 34)) {
        return 34;
    }
    if ((_v1222 == 39)) {
        return 39;
    }
    if ((_v1222 == 120)) {
        bkr_i64 _v1223 = _v1219(char_code_at(_v1212, (_v1213 + 2)));
        bkr_i64 _v1224 = _v1219(char_code_at(_v1212, (_v1213 + 3)));
        if (((_v1223 >= 0) && (_v1224 >= 0))) {
            vec_set(_v1221, 0, 4);
            return ((_v1223 * 16) + _v1224);
        }
    }
    return (-1);
}

bkr_i64 _v1225(bkr_i64 _v425, bkr_str _v1226) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v425))) {
        if (bkr_str_eq(vec_get(_v425, _v1172), _v1226)) {
            return _v1172;
        }
        _v1172 = (_v1172 + 1);
    }
    bkr_i64 _v1036 = vec_len(_v425);
    vec_push(_v425, ((bkr_i64)(intptr_t)_v1226));
    return _v1036;
}

bkr_i64 _v1227(bkr_str _v1212) {
    return _v1194(_v1228(_v1212));
}

_v1190 _v1228(bkr_str _v1212) {
    bkr_i64 _v1192 = vec_new();
    bkr_i64 _v425 = vec_new();
    bkr_i64 _v613 = vec_new();
    bkr_i64 _v1193 = vec_new();
    bkr_i64 _v1213 = 0;
    bkr_i64 _v1214 = bkr_len((bkr_str)(intptr_t)(_v1212));
    while ((_v1213 < _v1214)) {
        _v1213 = _v1211(_v1212, _v1213);
        if ((_v1213 >= _v1214)) {
            vec_push(_v1192, _v129);
            vec_push(_v1192, _v1213);
            vec_push(_v1192, _v1213);
            return _v1195(_v1192, _v425, _v613, _v1193);
        }
        bkr_i64 _v339 = _v1213;
        bkr_i64 _v1208 = char_code_at(_v1212, _v1213);
        bkr_i64 _v1229 = 0;
        bkr_bool _v1230 = BKR_FALSE;
        if (_v1207(_v1208)) {
            while (((_v1213 < _v1214) && _v1210(char_code_at(_v1212, _v1213)))) {
                _v1213 = (_v1213 + 1);
            }
            bkr_str _v1226 = substring(_v1212, _v339, _v1213);
            _v1229 = _v131;
            if (bkr_str_eq(_v1226, "kernel")) {
                _v1229 = _v137;
            }
            if (bkr_str_eq(_v1226, "struct")) {
                _v1229 = _v139;
            }
            if (bkr_str_eq(_v1226, "enum")) {
                _v1229 = _v138;
            }
            if (bkr_str_eq(_v1226, "fn")) {
                _v1229 = _v140;
            }
            if (bkr_str_eq(_v1226, "let")) {
                _v1229 = _v141;
            }
            if (bkr_str_eq(_v1226, "pub")) {
                _v1229 = _v197;
            }
            if (bkr_str_eq(_v1226, "mut")) {
                _v1229 = _v198;
            }
            if (bkr_str_eq(_v1226, "if")) {
                _v1229 = _v142;
            }
            if (bkr_str_eq(_v1226, "else")) {
                _v1229 = _v143;
            }
            if (bkr_str_eq(_v1226, "for")) {
                _v1229 = _v144;
            }
            if (bkr_str_eq(_v1226, "in")) {
                _v1229 = _v145;
            }
            if (bkr_str_eq(_v1226, "while")) {
                _v1229 = _v146;
            }
            if (bkr_str_eq(_v1226, "break")) {
                _v1229 = _v147;
            }
            if (bkr_str_eq(_v1226, "continue")) {
                _v1229 = _v148;
            }
            if (bkr_str_eq(_v1226, "loop")) {
                _v1229 = _v149;
            }
            if (bkr_str_eq(_v1226, "return")) {
                _v1229 = _v150;
            }
            if (bkr_str_eq(_v1226, "defer")) {
                _v1229 = _v153;
            }
            if (bkr_str_eq(_v1226, "type")) {
                _v1229 = _v154;
            }
            if (bkr_str_eq(_v1226, "as")) {
                _v1229 = _v155;
            }
            if (bkr_str_eq(_v1226, "match")) {
                _v1229 = _v151;
            }
            if (bkr_str_eq(_v1226, "const")) {
                _v1229 = _v152;
            }
            if (bkr_str_eq(_v1226, "true")) {
                _v1229 = _v135;
            }
            if (bkr_str_eq(_v1226, "false")) {
                _v1229 = _v136;
            }
            if (bkr_str_eq(_v1226, "i32")) {
                _v1229 = _v156;
            }
            if (bkr_str_eq(_v1226, "i64")) {
                _v1229 = _v157;
            }
            if (bkr_str_eq(_v1226, "f64")) {
                _v1229 = _v158;
            }
            if (bkr_str_eq(_v1226, "bool")) {
                _v1229 = _v159;
            }
            if (bkr_str_eq(_v1226, "str")) {
                _v1229 = _v160;
            }
            bkr_i64 _v1233 = _v1225(_v425, _v1226);
            vec_push(_v1192, _v1229);
            vec_push(_v1192, _v1233);
            vec_push(_v1192, _v1213);
            _v1230 = BKR_TRUE;
        }
        if (((!_v1230) && _v1209(_v1208))) {
            while (((_v1213 < _v1214) && _v1209(char_code_at(_v1212, _v1213)))) {
                _v1213 = (_v1213 + 1);
            }
            if (((((_v1213 + 1) < _v1214) && (char_code_at(_v1212, _v1213) == 46)) && _v1209(char_code_at(_v1212, (_v1213 + 1))))) {
                _v1213 = (_v1213 + 1);
                while (((_v1213 < _v1214) && _v1209(char_code_at(_v1212, _v1213)))) {
                    _v1213 = (_v1213 + 1);
                }
                bkr_str _v1235 = substring(_v1212, _v339, _v1213);
                vec_push(_v1192, _v134);
                vec_push(_v1192, vec_len(_v1193));
                vec_push(_v1192, _v1213);
                vec_push(_v1193, ((bkr_i64)(intptr_t)_v1235));
            } else {
                bkr_str _v1236 = substring(_v1212, _v339, _v1213);
                bkr_i64 _v1237 = parse_int(_v1236);
                vec_push(_v1192, _v132);
                vec_push(_v1192, vec_len(_v613));
                vec_push(_v1192, _v1213);
                vec_push(_v613, _v1237);
            }
            _v1230 = BKR_TRUE;
        }
        if (((!_v1230) && (_v1208 == 34))) {
            _v1213 = (_v1213 + 1);
            bkr_str _v1239 = "";
            bkr_i64 _v1240 = _v1213;
            bkr_bool _v1241 = BKR_TRUE;
            bkr_bool _v1242 = BKR_FALSE;
            bkr_i64 _v1243 = vec_new();
            vec_push(_v1243, 2);
            while (((_v1213 < _v1214) && (char_code_at(_v1212, _v1213) != 34))) {
                if (((char_code_at(_v1212, _v1213) == 92) && ((_v1213 + 1) < _v1214))) {
                    if ((!_v1242)) {
                        _v1239 = bkr_str_concat(_v1239, substring(_v1212, _v1240, _v1213));
                    }
                    bkr_i64 _v1244 = _v1220(_v1212, _v1213, _v1243);
                    if ((_v1244 < 0)) {
                        _v1241 = BKR_FALSE;
                    } else {
                        if ((_v1244 == 0)) {
                            _v1242 = BKR_TRUE;
                        } else {
                            if ((!_v1242)) {
                                _v1239 = bkr_str_concat(_v1239, from_char_code(_v1244));
                            }
                        }
                    }
                    _v1213 = (_v1213 + vec_get(_v1243, 0));
                    _v1240 = _v1213;
                } else {
                    _v1213 = (_v1213 + 1);
                }
            }
            if ((!_v1242)) {
                _v1239 = bkr_str_concat(_v1239, substring(_v1212, _v1240, _v1213));
            }
            if ((_v1213 >= _v1214)) {
                _v1241 = BKR_FALSE;
            }
            _v1213 = (_v1213 + 1);
            if (_v1241) {
                vec_push(_v1192, _v133);
                vec_push(_v1192, vec_len(_v1193));
                vec_push(_v1192, _v1213);
                vec_push(_v1193, ((bkr_i64)(intptr_t)_v1239));
            } else {
                vec_push(_v1192, 1);
                vec_push(_v1192, _v339);
                vec_push(_v1192, _v1213);
            }
            _v1230 = BKR_TRUE;
        }
        if (((!_v1230) && (_v1208 == 39))) {
            bkr_i64 _v1244 = (-1);
            bkr_i64 _v1246 = 0;
            bkr_i64 _v1243 = vec_new();
            vec_push(_v1243, 2);
            if ((((_v1213 + 1) < _v1214) && (char_code_at(_v1212, (_v1213 + 1)) == 92))) {
                _v1244 = _v1220(_v1212, (_v1213 + 1), _v1243);
                _v1246 = vec_get(_v1243, 0);
            } else {
                if (((_v1213 + 1) < _v1214)) {
                    _v1244 = char_code_at(_v1212, (_v1213 + 1));
                    _v1246 = 1;
                }
            }
            if (((_v1244 >= 0) && (char_code_at(_v1212, ((_v1213 + 1) + _v1246)) == 39))) {
                _v1213 = ((_v1213 + 2) + _v1246);
                vec_push(_v1192, _v132);
                vec_push(_v1192, vec_len(_v613));
                vec_push(_v1192, _v1213);
                vec_push(_v613, _v1244);
            } else {
                _v1213 = (_v1213 + 1);
                while ((((_v1213 < _v1214) && (char_code_at(_v1212, _v1213) != 39)) && (char_code_at(_v1212, _v1213) != 10))) {
                    _v1213 = (_v1213 + 1);
                }
                _v1213 = (_v1213 + 1);
                vec_push(_v1192, 1);
                vec_push(_v1192, _v339);
                vec_push(_v1192, _v1213);
            }
            _v1230 = BKR_TRUE;
        }
        if (((!_v1230) && ((_v1213 + 2) < _v1214))) {
            bkr_i64 _v1247 = char_code_at(_v1212, (_v1213 + 1));
            bkr_i64 _v1248 = char_code_at(_v1212, (_v1213 + 2));
            if ((((_v1208 == 46) && (_v1247 == 46)) && (_v1248 == 61))) {
                _v1229 = _v183;
                _v1213 = (_v1213 + 3);
                _v1230 = BKR_TRUE;
            }
            if (_v1230) {
                vec_push(_v1192, _v1229);
                vec_push(_v1192, _v339);
                vec_push(_v1192, _v1213);
            }
        }
        if (((!_v1230) && ((_v1213 + 1) < _v1214))) {
            bkr_i64 _v1247 = char_code_at(_v1212, (_v1213 + 1));
            if (((_v1208 == 45) && (_v1247 == 62))) {
                _v1229 = _v181;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 61)) && (_v1247 == 62))) {
                _v1229 = _v195;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 46)) && (_v1247 == 46))) {
                _v1229 = _v182;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 61)) && (_v1247 == 61))) {
                _v1229 = _v166;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 33)) && (_v1247 == 61))) {
                _v1229 = _v167;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 60)) && (_v1247 == 61))) {
                _v1229 = _v170;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 62)) && (_v1247 == 61))) {
                _v1229 = _v171;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 60)) && (_v1247 == 60))) {
                _v1229 = _v178;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 62)) && (_v1247 == 62))) {
                _v1229 = _v179;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 38)) && (_v1247 == 38))) {
                _v1229 = _v172;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 124)) && (_v1247 == 124))) {
                _v1229 = _v173;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if ((((!_v1230) && (_v1208 == 58)) && (_v1247 == 58))) {
                _v1229 = _v196;
                _v1213 = (_v1213 + 2);
                _v1230 = BKR_TRUE;
            }
            if (_v1230) {
                vec_push(_v1192, _v1229);
                vec_push(_v1192, _v339);
                vec_push(_v1192, _v1213);
            }
        }
        if ((!_v1230)) {
            if ((_v1208 == 43)) {
                _v1229 = _v161;
            }
            if ((_v1208 == 45)) {
                _v1229 = _v162;
            }
            if ((_v1208 == 42)) {
                _v1229 = _v163;
            }
            if ((_v1208 == 47)) {
                _v1229 = _v164;
            }
            if ((_v1208 == 37)) {
                _v1229 = _v165;
            }
            if ((_v1208 == 60)) {
                _v1229 = _v168;
            }
            if ((_v1208 == 62)) {
                _v1229 = _v169;
            }
            if ((_v1208 == 33)) {
                _v1229 = _v174;
            }
            if ((_v1208 == 38)) {
                _v1229 = _v175;
            }
            if ((_v1208 == 124)) {
                _v1229 = _v176;
            }
            if ((_v1208 == 94)) {
                _v1229 = _v177;
            }
            if ((_v1208 == 46)) {
                _v1229 = _v184;
            }
            if ((_v1208 == 61)) {
                _v1229 = _v180;
            }
            if ((_v1208 == 40)) {
                _v1229 = _v185;
            }
            if ((_v1208 == 41)) {
                _v1229 = _v186;
            }
            if ((_v1208 == 123)) {
                _v1229 = _v187;
            }
            if ((_v1208 == 125)) {
                _v1229 = _v188;
            }
            if ((_v1208 == 91)) {
                _v1229 = _v189;
            }
            if ((_v1208 == 93)) {
                _v1229 = _v190;
            }
            if ((_v1208 == 44)) {
                _v1229 = _v191;
            }
            if ((_v1208 == 59)) {
                _v1229 = _v192;
            }
            if ((_v1208 == 58)) {
                _v1229 = _v193;
            }
            if ((_v1208 == 63)) {
                _v1229 = _v194;
            }
            if ((_v1229 == 0)) {
                _v1229 = 1;
            }
            _v1213 = (_v1213 + 1);
            vec_push(_v1192, _v1229);
            vec_push(_v1192, _v339);
            vec_push(_v1192, _v1213);
        }
    }
    vec_push(_v1192, _v129);
    vec_push(_v1192, _v1213);
    vec_push(_v1192, _v1213);
    return _v1195(_v1192, _v425, _v613, _v1193);
}

bkr_i64 _v1250(bkr_i64 _v1251) {
    return _v1252(_v1253(_v1197(_v1251)));
}

_v1249 _v1253(_v1190 _v1251) {
    bkr_i64 _v1254 = vec_new();
    vec_push(_v1254, ((bkr_i64)(_v1200(_v1251))));
    vec_push(_v1254, ((bkr_i64)(_v1202(_v1251))));
    vec_push(_v1254, ((bkr_i64)(_v1204(_v1251))));
    vec_push(_v1254, ((bkr_i64)(_v1206(_v1251))));
    vec_push(_v1254, 0);
    vec_push(_v1254, 0);
    vec_push(_v1254, (-1));
    vec_push(_v1254, _v129);
    vec_push(_v1254, _v129);
    bkr_i64 _v1255 = vec_new();
    bkr_i64 _v1256 = vec_new();
    bkr_i64 _v1257 = vec_new();
    vec_push(_v1254, ((bkr_i64)(_v1255)));
    vec_push(_v1254, ((bkr_i64)(_v1256)));
    vec_push(_v1254, ((bkr_i64)(_v1257)));
    return _v1258(_v1254);
}

_v1249 _v1258(bkr_i64 _v1254) {
    return (_v1249){._v342 = ((bkr_i64)(_v1254))};
}

bkr_i64 _v1252(_v1249 _v1259) {
    return ((bkr_i64)(_v1259._v342));
}

bkr_i64 _v1260(bkr_i64 _v1261) {
    return _v1262(_v1258(_v1261));
}

bkr_i64 _v1262(_v1249 _v1259) {
    return ((bkr_i64)(vec_get(_v1252(_v1259), 0)));
}

bkr_i64 _v1263(bkr_i64 _v1261) {
    return _v1264(_v1258(_v1261));
}

bkr_i64 _v1264(_v1249 _v1259) {
    return ((bkr_i64)(vec_get(_v1252(_v1259), 1)));
}

bkr_i64 _v1265(bkr_i64 _v1261) {
    return _v1266(_v1258(_v1261));
}

bkr_i64 _v1266(_v1249 _v1259) {
    return ((bkr_i64)(vec_get(_v1252(_v1259), 2)));
}

bkr_i64 _v1267(bkr_i64 _v1261) {
    return _v1268(_v1258(_v1261));
}

bkr_i64 _v1268(_v1249 _v1259) {
    return ((bkr_i64)(vec_get(_v1252(_v1259), 3)));
}

bkr_i64 _v1269(bkr_i64 _v1261) {
    return _v1270(_v1258(_v1261));
}

bkr_i64 _v1270(_v1249 _v1259) {
    return vec_get(_v1252(_v1259), 4);
}

bkr_i64 _v1271(bkr_i64 _v1261, bkr_i64 _v1213) {
    _v1272(_v1258(_v1261), _v1213);
    return _v1261;
}

_v1249 _v1272(_v1249 _v1259, bkr_i64 _v1213) {
    vec_set(_v1252(_v1259), 4, _v1213);
    return _v1259;
}

bkr_i64 _v1273(bkr_i64 _v1261, bkr_i64 _v1274) {
    _v1275(_v1258(_v1261), _v1274);
    return _v1261;
}

_v1249 _v1275(_v1249 _v1259, bkr_i64 _v1274) {
    vec_set(_v1252(_v1259), 5, _v1274);
    return _v1259;
}

bkr_i64 _v1276(bkr_i64 _v1261, bkr_i64 _v1213) {
    _v1277(_v1258(_v1261), _v1213);
    return _v1261;
}

_v1249 _v1277(_v1249 _v1259, bkr_i64 _v1213) {
    vec_set(_v1252(_v1259), 6, _v1213);
    return _v1259;
}

bkr_i64 _v1278(bkr_i64 _v1261, bkr_i64 _v1279) {
    _v1280(_v1258(_v1261), _v1279);
    return _v1261;
}

_v1249 _v1280(_v1249 _v1259, bkr_i64 _v1279) {
    vec_set(_v1252(_v1259), 7, _v1279);
    return _v1259;
}

bkr_i64 _v1281(bkr_i64 _v1261, bkr_i64 _v1282) {
    _v1283(_v1258(_v1261), _v1282);
    return _v1261;
}

_v1249 _v1283(_v1249 _v1259, bkr_i64 _v1282) {
    vec_set(_v1252(_v1259), 8, _v1282);
    return _v1259;
}

bkr_i64 _v1284(bkr_i64 _v1261) {
    return _v1285(_v1258(_v1261));
}

bkr_i64 _v1285(_v1249 _v1259) {
    bkr_i64 _v1192 = _v1262(_v1259);
    bkr_i64 _v1213 = _v1270(_v1259);
    bkr_i64 _v1036 = (_v1213 * 3);
    if ((_v1036 >= vec_len(_v1192))) {
        return 0;
    }
    return vec_get(_v1192, _v1036);
}

bkr_i64 _v1286(bkr_i64 _v1261) {
    return _v1287(_v1258(_v1261));
}

bkr_i64 _v1287(_v1249 _v1259) {
    bkr_i64 _v1192 = _v1262(_v1259);
    bkr_i64 _v1213 = _v1270(_v1259);
    return vec_get(_v1192, ((_v1213 * 3) + 1));
}

bkr_i64 _v1288(bkr_i64 _v1261, bkr_i64 _v1289) {
    return _v1290(_v1258(_v1261), _v1289);
}

bkr_i64 _v1290(_v1249 _v1259, bkr_i64 _v1289) {
    bkr_i64 _v1192 = _v1262(_v1259);
    bkr_i64 _v1213 = (_v1270(_v1259) + _v1289);
    bkr_i64 _v1036 = (_v1213 * 3);
    if ((_v1036 >= vec_len(_v1192))) {
        return 0;
    }
    return vec_get(_v1192, _v1036);
}

bkr_i64 _v1291(bkr_i64 _v1261) {
    return _v1292(_v1258(_v1261));
}

bkr_i64 _v1292(_v1249 _v1259) {
    _v1272(_v1259, (_v1270(_v1259) + 1));
    return _v1285(_v1259);
}

bkr_bool _v1293(bkr_i64 _v1261, bkr_i64 _v1279) {
    return _v1294(_v1258(_v1261), _v1279);
}

bkr_bool _v1294(_v1249 _v1259, bkr_i64 _v1279) {
    if ((_v1285(_v1259) == _v1279)) {
        _v1292(_v1259);
        return BKR_TRUE;
    }
    if (((_v1279 == _v169) && (_v1285(_v1259) == _v179))) {
        bkr_i64 _v1036 = (_v1270(_v1259) * 3);
        vec_set(_v1262(_v1259), _v1036, _v169);
        return BKR_TRUE;
    }
    _v1295(_v1259, _v1279);
    return BKR_FALSE;
}

bkr_i64 _v1296(bkr_i64 _v1261, bkr_i64 _v1279) {
    _v1295(_v1258(_v1261), _v1279);
    return _v1261;
}

_v1249 _v1295(_v1249 _v1259, bkr_i64 _v1279) {
    _v1275(_v1259, 1);
    bkr_i64 _v1297 = _v1270(_v1259);
    bkr_i64 _v1298 = _v1285(_v1259);
    if ((_v1299(_v1259) < 0)) {
        _v1277(_v1259, _v1297);
        _v1280(_v1259, _v1279);
        _v1283(_v1259, _v1298);
    }
    bkr_i64 _v1254 = _v1252(_v1259);
    if ((vec_len(_v1254) >= 12)) {
        bkr_i64 _v1255 = ((bkr_i64)(vec_get(_v1254, 9)));
        bkr_i64 _v1256 = ((bkr_i64)(vec_get(_v1254, 10)));
        bkr_i64 _v1257 = ((bkr_i64)(vec_get(_v1254, 11)));
        bkr_bool _v1300 = BKR_FALSE;
        bkr_i64 _v1172 = 0;
        while ((_v1172 < vec_len(_v1255))) {
            if ((vec_get(_v1255, _v1172) == _v1297)) {
                _v1300 = BKR_TRUE;
                break;
            }
            _v1172 = (_v1172 + 1);
        }
        if ((!_v1300)) {
            vec_push(_v1255, _v1297);
            vec_push(_v1256, _v1279);
            vec_push(_v1257, _v1298);
        }
    }
    return _v1259;
}

bkr_str _v1302(bkr_i64 _v1261, bkr_i64 _v1036) {
    return _v1303(_v1258(_v1261), _v1036);
}

bkr_str _v1303(_v1249 _v1259, bkr_i64 _v1036) {
    bkr_i64 _v425 = _v1264(_v1259);
    if (((_v1036 < 0) || (_v1036 >= vec_len(_v425)))) {
        return "";
    }
    return vec_get(_v425, _v1036);
}

bkr_i64 _v1304(_v1249 _v1259, bkr_str _v1305) {
    bkr_i64 _v425 = _v1264(_v1259);
    bkr_i64 _v1172 = 0;
    bkr_i64 _v399 = vec_len(_v425);
    while ((_v1172 < _v399)) {
        if (bkr_str_eq(vec_get(_v425, _v1172), _v1305)) {
            return _v1172;
        }
        _v1172 = (_v1172 + 1);
    }
    vec_push(_v425, ((bkr_i64)(intptr_t)_v1305));
    return _v399;
}

bkr_i64 _v1306(bkr_i64 _v1261, bkr_i64 _v1036) {
    return _v1307(_v1258(_v1261), _v1036);
}

bkr_i64 _v1307(_v1249 _v1259, bkr_i64 _v1036) {
    return vec_get(_v1266(_v1259), _v1036);
}

bkr_str _v1308(bkr_i64 _v1261, bkr_i64 _v1036) {
    return _v1309(_v1258(_v1261), _v1036);
}

bkr_str _v1309(_v1249 _v1259, bkr_i64 _v1036) {
    bkr_i64 _v1193 = _v1268(_v1259);
    if (((_v1036 < 0) || (_v1036 >= vec_len(_v1193)))) {
        return "";
    }
    return vec_get(_v1193, _v1036);
}

bkr_bool _v1310(bkr_i64 _v1261) {
    return _v1311(_v1258(_v1261));
}

bkr_bool _v1311(_v1249 _v1259) {
    return (vec_get(_v1252(_v1259), 5) != 0);
}

bkr_i64 _v1312(bkr_i64 _v1261) {
    return _v1299(_v1258(_v1261));
}

bkr_i64 _v1299(_v1249 _v1259) {
    return vec_get(_v1252(_v1259), 6);
}

bkr_i64 _v1313(bkr_i64 _v1261) {
    return _v1314(_v1258(_v1261));
}

bkr_i64 _v1314(_v1249 _v1259) {
    return vec_get(_v1252(_v1259), 7);
}

bkr_i64 _v1315(bkr_i64 _v1261) {
    return _v1316(_v1258(_v1261));
}

bkr_i64 _v1316(_v1249 _v1259) {
    return vec_get(_v1252(_v1259), 8);
}

bkr_i64 _v1317(_v1249 _v1259) {
    bkr_i64 _v1254 = _v1252(_v1259);
    if ((vec_len(_v1254) < 12)) {
        if (_v1311(_v1259)) {
            return 1;
        }
        return 0;
    }
    bkr_i64 _v1255 = ((bkr_i64)(vec_get(_v1254, 9)));
    bkr_i64 _v399 = vec_len(_v1255);
    if (((_v399 == 0) && _v1311(_v1259))) {
        return 1;
    }
    return _v399;
}

bkr_i64 _v1318(_v1249 _v1259, bkr_i64 _v1036) {
    bkr_i64 _v1254 = _v1252(_v1259);
    if ((vec_len(_v1254) < 12)) {
        return _v1299(_v1259);
    }
    bkr_i64 _v1255 = ((bkr_i64)(vec_get(_v1254, 9)));
    if (((_v1036 >= 0) && (_v1036 < vec_len(_v1255)))) {
        return vec_get(_v1255, _v1036);
    }
    return _v1299(_v1259);
}

bkr_i64 _v1319(_v1249 _v1259, bkr_i64 _v1036) {
    bkr_i64 _v1254 = _v1252(_v1259);
    if ((vec_len(_v1254) < 12)) {
        return _v1314(_v1259);
    }
    bkr_i64 _v1256 = ((bkr_i64)(vec_get(_v1254, 10)));
    if (((_v1036 >= 0) && (_v1036 < vec_len(_v1256)))) {
        return vec_get(_v1256, _v1036);
    }
    return _v1314(_v1259);
}

bkr_i64 _v1320(_v1249 _v1259, bkr_i64 _v1036) {
    bkr_i64 _v1254 = _v1252(_v1259);
    if ((vec_len(_v1254) < 12)) {
        return _v1316(_v1259);
    }
    bkr_i64 _v1257 = ((bkr_i64)(vec_get(_v1254, 11)));
    if (((_v1036 >= 0) && (_v1036 < vec_len(_v1257)))) {
        return vec_get(_v1257, _v1036);
    }
    return _v1316(_v1259);
}

bkr_str _v1321(bkr_i64 _v1322) {
    return _v324(_v1322);
}

bkr_bool _v1323(bkr_i64 _v1322) {
    return _v325(_v1322);
}

bkr_i64 _v1324(bkr_i64 _v1261, bkr_i64 _v1213) {
    return _v1325(_v1258(_v1261), _v1213);
}

bkr_i64 _v1325(_v1249 _v1261, bkr_i64 _v1213) {
    bkr_i64 _v1192 = _v1262(_v1261);
    bkr_i64 _v1036 = (_v1213 * 3);
    if (((_v1213 < 0) || ((_v1036 + 2) >= vec_len(_v1192)))) {
        return 0;
    }
    return vec_get(_v1192, (_v1036 + 2));
}

bkr_i64 _v1326(bkr_i64 _v1261, bkr_i64 _v1213) {
    return _v1327(_v1258(_v1261), _v1213);
}

bkr_i64 _v1327(_v1249 _v1261, bkr_i64 _v1213) {
    bkr_i64 _v1192 = _v1262(_v1261);
    bkr_i64 _v1036 = (_v1213 * 3);
    if (((_v1213 < 0) || ((_v1036 + 2) >= vec_len(_v1192)))) {
        return 0;
    }
    bkr_i64 _v1322 = vec_get(_v1192, _v1036);
    bkr_i64 _v387 = vec_get(_v1192, (_v1036 + 1));
    bkr_i64 _v340 = vec_get(_v1192, (_v1036 + 2));
    if ((_v1322 == _v129)) {
        return _v340;
    }
    if ((_v1322 == _v131)) {
        return (_v340 - bkr_len((bkr_str)(intptr_t)(_v1303(_v1261, _v387))));
    }
    if ((_v1322 == _v132)) {
        return (_v340 - bkr_len((bkr_str)(intptr_t)(int_to_string(_v1307(_v1261, _v387)))));
    }
    if ((_v1322 == _v133)) {
        return ((_v340 - bkr_len((bkr_str)(intptr_t)(_v1309(_v1261, _v387)))) - 2);
    }
    if ((_v1322 == _v134)) {
        return (_v340 - bkr_len((bkr_str)(intptr_t)(_v1309(_v1261, _v387))));
    }
    if (_v1323(_v1322)) {
        return (_v340 - bkr_len((bkr_str)(intptr_t)(_v1321(_v1322))));
    }
    return _v387;
}

bkr_i64 _v1328(_v1249 _v1261) {
    return _v1327(_v1261, _v1270(_v1261));
}

bkr_i64 _v1329(_v1249 _v1261) {
    bkr_i64 _v1213 = (_v1270(_v1261) - 1);
    if ((_v1213 < 0)) {
        return _v1328(_v1261);
    }
    return _v1325(_v1261, _v1213);
}

bkr_i64 _v1330(_v1249 _v1261, bkr_i64 _v339) {
    bkr_i64 _v340 = _v1329(_v1261);
    if ((_v340 < _v339)) {
        return _v1325(_v1261, _v1270(_v1261));
    }
    return _v340;
}

_v338 _v1331(_v1249 _v1261, bkr_i64 _v339) {
    return _v480(_v339, _v1330(_v1261, _v339));
}

_v341 _v1332(_v1249 _v1261, _v341 _v452, bkr_i64 _v339) {
    return _v454(_v452, _v339, _v1330(_v1261, _v339));
}

_v341 _v1333(_v341 _v452, bkr_i64 _v339, bkr_i64 _v340) {
    return _v454(_v452, _v339, _v340);
}

_v346 _v1334(_v1249 _v1261, _v346 _v521, bkr_i64 _v339) {
    _v1332(_v1261, _v586(_v521), _v339);
    return _v521;
}

_v426 _v1335(_v1249 _v1261, _v426 _v542, bkr_i64 _v339) {
    _v1332(_v1261, _v547(_v542), _v339);
    return _v542;
}

_v426 _v1336(_v426 _v542, bkr_i64 _v339, bkr_i64 _v340) {
    _v1333(_v547(_v542), _v339, _v340);
    return _v542;
}

_v427 _v1337(_v1249 _v1261, _v427 _v554, bkr_i64 _v339) {
    _v1332(_v1261, _v587(_v554), _v339);
    return _v554;
}

_v427 _v1338(_v427 _v554, bkr_i64 _v339, bkr_i64 _v340) {
    _v1333(_v587(_v554), _v339, _v340);
    return _v554;
}

_v428 _v1339(_v1249 _v1261, _v428 _v563, bkr_i64 _v339) {
    _v1332(_v1261, _v588(_v563), _v339);
    return _v563;
}

_v429 _v1340(_v1249 _v1261, _v429 _v583, bkr_i64 _v339) {
    _v1332(_v1261, _v589(_v583), _v339);
    return _v583;
}

bkr_i64 _v1341(_v1249 _v1261, bkr_i64 _v447, bkr_i64 _v339) {
    return _v1342(_v1332(_v1261, _v477(_v447), _v339));
}

_v433 _v1343(_v1249 _v1261, _v433 _v473, bkr_i64 _v339) {
    return _v472(_v473, _v339, _v1330(_v1261, _v339));
}

bkr_i64 _v1344(_v1249 _v1261, bkr_i64 _v463, bkr_i64 _v339) {
    return _v1345(_v1343(_v1261, _v593(_v463), _v339));
}

bkr_i64 _v1342(_v341 _v452) {
    return _v453(_v452);
}

bkr_i64 _v1346(_v346 _v521) {
    return _v527(_v521);
}

bkr_i64 _v1347(_v426 _v542) {
    return _v544(_v542);
}

bkr_i64 _v1348(_v427 _v554) {
    return _v555(_v554);
}

bkr_i64 _v1349(_v428 _v563) {
    return _v568(_v563);
}

bkr_i64 _v1350(_v429 _v583) {
    return _v585(_v583);
}

bkr_i64 _v1345(_v433 _v473) {
    return _v474(_v473);
}

bkr_i64 _v1351(_v434 _v608) {
    return _v609(_v608);
}

_v338 _v1352(bkr_i64 _v1261) {
    return _v1353(_v1258(_v1261));
}

_v338 _v1353(_v1249 _v1261) {
    bkr_i64 _v1213 = _v1299(_v1261);
    return _v480(_v1327(_v1261, _v1213), _v1325(_v1261, _v1213));
}

_v338 _v1354(_v1249 _v1261, bkr_i64 _v1036) {
    bkr_i64 _v1213 = _v1318(_v1261, _v1036);
    return _v480(_v1327(_v1261, _v1213), _v1325(_v1261, _v1213));
}

bkr_bool _v1355(_v1249 _v1261) {
    while ((((_v1285(_v1261) != _v192) && (_v1285(_v1261) != _v188)) && (_v1285(_v1261) != _v129))) {
        _v1292(_v1261);
    }
    if ((_v1285(_v1261) == _v192)) {
        _v1292(_v1261);
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v1356(_v1249 _v1261) {
    while (((((((((_v1285(_v1261) != _v140) && (_v1285(_v1261) != _v152)) && (_v1285(_v1261) != _v139)) && (_v1285(_v1261) != _v138)) && (_v1285(_v1261) != _v154)) && (_v1285(_v1261) != _v197)) && (_v1285(_v1261) != _v188)) && (_v1285(_v1261) != _v129))) {
        _v1292(_v1261);
    }
    return (_v1285(_v1261) != _v129);
}

bkr_i64 _v1357(bkr_i64 _v1261) {
    return _v1358(_v1258(_v1261));
}

bkr_i64 _v1358(_v1249 _v1261) {
    return _v483(_v1353(_v1261));
}

bkr_i64 _v1359(bkr_i64 _v1261) {
    return _v1360(_v1258(_v1261));
}

bkr_i64 _v1360(_v1249 _v1261) {
    return _v482(_v1353(_v1261));
}

bkr_i64 _v1361(_v1249 _v1261) {
    bkr_i64 _v387 = _v1287(_v1261);
    if (_v1323(_v1285(_v1261))) {
        _v1292(_v1261);
        return _v387;
    }
    _v1295(_v1261, _v131);
    return _v1304(_v1261, "");
}

bkr_bool _v1362(_v1249 _v1261, bkr_str _v1363) {
    if ((_v1285(_v1261) != _v131)) {
        return BKR_FALSE;
    }
    return bkr_str_eq(_v1303(_v1261, _v1287(_v1261)), _v1363);
}

_v1249 _v1364(_v1249 _v1261) {
    if ((_v1285(_v1261) == _v168)) {
        bkr_i64 _v1365 = 0;
        while ((_v1285(_v1261) != _v129)) {
            bkr_i64 _v1322 = _v1285(_v1261);
            if ((_v1322 == _v168)) {
                _v1365 = (_v1365 + 1);
            }
            if ((_v1322 == _v169)) {
                _v1365 = (_v1365 - 1);
            }
            _v1292(_v1261);
            if ((_v1365 <= 0)) {
                return _v1261;
            }
        }
    }
    return _v1261;
}

bkr_i64 _v1366(_v1249 _v1261) {
    return _v1346(_v1367(_v1261));
}

_v346 _v1367(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    bkr_i64 _v1322 = _v1285(_v1261);
    bkr_i64 _v319 = _v303;
    bkr_bool _v1368 = BKR_FALSE;
    if ((_v1322 == _v185)) {
        _v1292(_v1261);
        if ((_v1285(_v1261) == _v186)) {
            _v1292(_v1261);
            return _v1334(_v1261, _v960(_v307), _v339);
        }
        _v346 _v1369 = _v1367(_v1261);
        while ((_v1285(_v1261) == _v191)) {
            _v1292(_v1261);
            _v346 _v1370 = _v1367(_v1261);
        }
        _v1294(_v1261, _v186);
        return _v1334(_v1261, _v960(_v303), _v339);
    }
    if ((_v1322 == _v189)) {
        _v1292(_v1261);
        _v346 _v1371 = _v1367(_v1261);
        _v1294(_v1261, _v192);
        bkr_i64 _v955 = 0;
        if ((_v1285(_v1261) == _v132)) {
            _v955 = _v1307(_v1261, _v1287(_v1261));
            _v1292(_v1261);
        } else {
            _v1295(_v1261, _v132);
        }
        _v1294(_v1261, _v190);
        return _v1334(_v1261, _v962(_v530(_v1371), _v955), _v339);
    }
    if ((_v1322 == _v140)) {
        _v1292(_v1261);
        _v1294(_v1261, _v185);
        if ((_v1285(_v1261) != _v186)) {
            _v346 _v1372 = _v1367(_v1261);
            while ((_v1285(_v1261) == _v191)) {
                _v1292(_v1261);
                if ((_v1285(_v1261) != _v186)) {
                    _v346 _v1373 = _v1367(_v1261);
                }
            }
        }
        _v1294(_v1261, _v186);
        if ((_v1285(_v1261) == _v181)) {
            _v1292(_v1261);
            _v346 _v1374 = _v1367(_v1261);
            bkr_i64 _v1375 = _v530(_v1374);
            return _v1334(_v1261, _v966(13, _v1375, 0), _v339);
        }
        return _v1334(_v1261, _v966(13, _v307, 0), _v339);
    }
    if ((_v1322 == _v174)) {
        _v1292(_v1261);
        return _v1334(_v1261, _v960(_v314), _v339);
    }
    if ((_v1322 == _v156)) {
        _v319 = _v302;
        _v1292(_v1261);
        _v1368 = BKR_TRUE;
    }
    if ((_v1322 == _v157)) {
        _v319 = _v303;
        _v1292(_v1261);
        _v1368 = BKR_TRUE;
    }
    if ((_v1322 == _v158)) {
        _v319 = _v304;
        _v1292(_v1261);
        _v1368 = BKR_TRUE;
    }
    if ((_v1322 == _v159)) {
        _v319 = _v305;
        _v1292(_v1261);
        _v1368 = BKR_TRUE;
    }
    if ((_v1322 == _v160)) {
        _v319 = _v306;
        _v1292(_v1261);
        _v1368 = BKR_TRUE;
    }
    if ((_v1322 == _v131)) {
        bkr_i64 _v355 = _v1287(_v1261);
        bkr_str _v1363 = _v1303(_v1261, _v355);
        if ((bkr_str_eq(_v1363, "never") && (_v1285(_v1261) != _v168))) {
            _v1292(_v1261);
            return _v1334(_v1261, _v960(_v314), _v339);
        }
        _v1292(_v1261);
        if ((_v1285(_v1261) == _v168)) {
            if (bkr_str_eq(_v1363, "Vec")) {
                _v1292(_v1261);
                _v346 _v1001 = _v1367(_v1261);
                bkr_i64 _v954 = _v530(_v1001);
                bkr_i64 _v1376 = _v532(_v1001);
                _v1294(_v1261, _v169);
                return _v1334(_v1261, _v966(8, _v954, _v1376), _v339);
            }
            if (bkr_str_eq(_v1363, "HashMap")) {
                _v1292(_v1261);
                _v346 _v1377 = _v1367(_v1261);
                bkr_i64 _v1378 = _v530(_v1377);
                _v1294(_v1261, _v191);
                _v346 _v1379 = _v1367(_v1261);
                bkr_i64 _v1380 = _v530(_v1379);
                _v1294(_v1261, _v169);
                return _v1334(_v1261, _v966(9, _v1378, _v1380), _v339);
            }
            if (bkr_str_eq(_v1363, "Option")) {
                _v1292(_v1261);
                _v346 _v1381 = _v1367(_v1261);
                bkr_i64 _v1382 = _v530(_v1381);
                bkr_i64 _v1383 = _v532(_v1381);
                _v1294(_v1261, _v169);
                return _v1334(_v1261, _v966(10, _v1382, _v1383), _v339);
            }
            if (bkr_str_eq(_v1363, "Result")) {
                _v1292(_v1261);
                _v346 _v1384 = _v1367(_v1261);
                bkr_i64 _v1385 = _v530(_v1384);
                _v1294(_v1261, _v191);
                _v346 _v1386 = _v1367(_v1261);
                bkr_i64 _v1387 = _v530(_v1386);
                _v1294(_v1261, _v169);
                return _v1334(_v1261, _v966(11, _v1385, _v1387), _v339);
            }
            _v1364(_v1261);
            _v1368 = BKR_TRUE;
        } else {
            return _v1334(_v1261, _v964(_v355), _v339);
        }
    }
    if (((!_v1368) && (_v1322 != _v129))) {
        _v1292(_v1261);
    }
    return _v1334(_v1261, _v960(_v319), _v339);
}

bkr_i64 _v1388(_v1249 _v1261) {
    return _v1345(_v1389(_v1261));
}

_v433 _v1389(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    bkr_i64 _v1322 = _v1285(_v1261);
    if ((_v1322 == _v185)) {
        _v1292(_v1261);
        if ((_v1285(_v1261) == _v186)) {
            _v1292(_v1261);
            return _v1343(_v1261, _v468(_v286, 0), _v339);
        }
        bkr_i64 _v1390 = vec_new();
        _v433 _v1391 = _v1389(_v1261);
        vec_push(_v1390, _v594(_v1391));
        bkr_i64 _v1392 = (-1);
        if ((_v597(_v1391) == _v285)) {
            _v1392 = _v598(_v1391);
        }
        bkr_i64 _v432 = (-1);
        bkr_i64 _v1393 = (-1);
        if ((_v1285(_v1261) == _v191)) {
            _v1292(_v1261);
            if ((_v1285(_v1261) != _v186)) {
                _v433 _v1394 = _v1389(_v1261);
                vec_push(_v1390, _v594(_v1394));
                if ((_v597(_v1394) == _v285)) {
                    _v432 = _v598(_v1394);
                }
                if ((_v1285(_v1261) == _v191)) {
                    _v1292(_v1261);
                    if ((_v1285(_v1261) != _v186)) {
                        _v433 _v1395 = _v1389(_v1261);
                        vec_push(_v1390, _v594(_v1395));
                        if ((_v597(_v1395) == _v285)) {
                            _v1393 = _v598(_v1395);
                        }
                        if ((_v1285(_v1261) == _v191)) {
                            _v1292(_v1261);
                        }
                    }
                }
            }
        }
        _v1294(_v1261, _v186);
        bkr_i64 _v1396 = ((bkr_i64)(_v1390));
        return _v1343(_v1261, _v471(_v292, _v1393, _v1396, _v1392, _v432), _v339);
    }
    if ((_v1322 == _v132)) {
        bkr_i64 _v1397 = _v1287(_v1261);
        bkr_i64 _v1398 = _v1307(_v1261, _v1397);
        _v1292(_v1261);
        return _v1343(_v1261, _v468(_v283, _v1398), _v339);
    }
    if ((_v1322 == _v135)) {
        _v1292(_v1261);
        return _v1343(_v1261, _v468(_v284, 1), _v339);
    }
    if ((_v1322 == _v136)) {
        _v1292(_v1261);
        return _v1343(_v1261, _v468(_v284, 0), _v339);
    }
    if (_v1323(_v1322)) {
        bkr_i64 _v355 = _v1287(_v1261);
        bkr_str _v1399 = _v1303(_v1261, _v355);
        _v1292(_v1261);
        if ((_v1285(_v1261) == _v187)) {
            _v1292(_v1261);
            bkr_i64 _v1400 = (-1);
            bkr_i64 _v1401 = (-1);
            bkr_i64 _v1402 = (-1);
            if ((_v1285(_v1261) != _v188)) {
                _v1400 = _v1361(_v1261);
                if ((_v1285(_v1261) == _v193)) {
                    _v1292(_v1261);
                    _v1400 = _v1361(_v1261);
                }
                if ((_v1285(_v1261) == _v191)) {
                    _v1292(_v1261);
                    if ((_v1285(_v1261) != _v188)) {
                        _v1401 = _v1361(_v1261);
                        if ((_v1285(_v1261) == _v193)) {
                            _v1292(_v1261);
                            _v1401 = _v1361(_v1261);
                        }
                        if ((_v1285(_v1261) == _v191)) {
                            _v1292(_v1261);
                            if ((_v1285(_v1261) != _v188)) {
                                _v1402 = _v1361(_v1261);
                                if ((_v1285(_v1261) == _v193)) {
                                    _v1292(_v1261);
                                    _v1402 = _v1361(_v1261);
                                }
                            }
                        }
                    }
                }
            }
            _v1294(_v1261, _v188);
            return _v1343(_v1261, _v471(_v293, _v355, _v1402, _v1400, _v1401), _v339);
        }
        if ((_v1285(_v1261) == _v184)) {
            _v1292(_v1261);
            bkr_i64 _v1403 = _v1361(_v1261);
            bkr_str _v1404 = _v1303(_v1261, _v1403);
            bkr_i64 _v1405 = (-1);
            bkr_i64 _v1406 = (-1);
            bkr_i64 _v1407 = 0;
            if ((_v1285(_v1261) == _v185)) {
                _v1292(_v1261);
                _v433 _v1408 = _v1389(_v1261);
                if ((_v597(_v1408) == _v285)) {
                    _v1405 = _v598(_v1408);
                } else {
                    _v1407 = _v594(_v1408);
                }
                if ((_v1285(_v1261) == _v191)) {
                    _v1292(_v1261);
                    _v1406 = _v1361(_v1261);
                }
                _v1294(_v1261, _v186);
            }
            if (bkr_str_eq(_v1399, "Option")) {
                if (bkr_str_eq(_v1404, "Some")) {
                    return _v1343(_v1261, _v469(_v287, _v1405, _v1407), _v339);
                }
                if (bkr_str_eq(_v1404, "None")) {
                    return _v1343(_v1261, _v468(_v288, 0), _v339);
                }
            }
            if (bkr_str_eq(_v1399, "Result")) {
                if (bkr_str_eq(_v1404, "Ok")) {
                    return _v1343(_v1261, _v469(_v290, _v1405, _v1407), _v339);
                }
                if (bkr_str_eq(_v1404, "Err")) {
                    return _v1343(_v1261, _v469(_v291, _v1405, _v1407), _v339);
                }
            }
            return _v1343(_v1261, _v471(_v289, _v355, _v1403, _v1405, _v1406), _v339);
        }
        if (bkr_str_eq(_v1399, "_")) {
            return _v1343(_v1261, _v468(_v286, 0), _v339);
        }
        if ((bkr_str_eq(_v1399, "Some") && (_v1285(_v1261) == _v185))) {
            _v1292(_v1261);
            _v433 _v1408 = _v1389(_v1261);
            _v1294(_v1261, _v186);
            bkr_i64 _v1405 = (-1);
            bkr_i64 _v1409 = 0;
            if ((_v597(_v1408) == _v285)) {
                _v1405 = _v598(_v1408);
            } else {
                _v1409 = _v594(_v1408);
            }
            return _v1343(_v1261, _v469(_v287, _v1405, _v1409), _v339);
        }
        if (bkr_str_eq(_v1399, "None")) {
            return _v1343(_v1261, _v468(_v288, 0), _v339);
        }
        if ((bkr_str_eq(_v1399, "Ok") && (_v1285(_v1261) == _v185))) {
            _v1292(_v1261);
            _v433 _v1408 = _v1389(_v1261);
            _v1294(_v1261, _v186);
            bkr_i64 _v1405 = (-1);
            bkr_i64 _v1409 = 0;
            if ((_v597(_v1408) == _v285)) {
                _v1405 = _v598(_v1408);
            } else {
                _v1409 = _v594(_v1408);
            }
            return _v1343(_v1261, _v469(_v290, _v1405, _v1409), _v339);
        }
        if ((bkr_str_eq(_v1399, "Err") && (_v1285(_v1261) == _v185))) {
            _v1292(_v1261);
            _v433 _v1408 = _v1389(_v1261);
            _v1294(_v1261, _v186);
            bkr_i64 _v1405 = (-1);
            bkr_i64 _v1409 = 0;
            if ((_v597(_v1408) == _v285)) {
                _v1405 = _v598(_v1408);
            } else {
                _v1409 = _v594(_v1408);
            }
            return _v1343(_v1261, _v469(_v291, _v1405, _v1409), _v339);
        }
        if ((_v1285(_v1261) == _v185)) {
            _v1292(_v1261);
            bkr_i64 _v1391 = _v1361(_v1261);
            bkr_i64 _v1394 = (-1);
            bkr_i64 _v1395 = (-1);
            if ((_v1285(_v1261) == _v191)) {
                _v1292(_v1261);
                _v1394 = _v1361(_v1261);
                if ((_v1285(_v1261) == _v191)) {
                    _v1292(_v1261);
                    _v1395 = _v1361(_v1261);
                }
            }
            _v1294(_v1261, _v186);
            return _v1343(_v1261, _v471(_v293, _v355, _v1395, _v1391, _v1394), _v339);
        }
        return _v1343(_v1261, _v468(_v285, _v355), _v339);
    }
    _v1295(_v1261, _v131);
    if ((_v1322 != _v129)) {
        _v1292(_v1261);
    }
    return _v1343(_v1261, _v468(_v286, 0), _v339);
}

bkr_i64 _v1410(_v1249 _v1261) {
    return _v1347(_v1411(_v1261));
}

_v426 _v1411(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1294(_v1261, _v151);
    _v426 _v975 = _v1412(_v1261);
    _v1294(_v1261, _v187);
    bkr_i64 _v406 = vec_new();
    bkr_i64 _v407 = vec_new();
    bkr_i64 _v408 = vec_new();
    _v436 _v621 = _v619(_v406);
    _v434 _v976 = _v605(_v407);
    _v435 _v977 = _v612(_v408);
    while (((_v1285(_v1261) != _v188) && (_v1285(_v1261) != _v129))) {
        _v433 _v473 = _v1389(_v1261);
        bkr_i64 _v1413 = 0;
        if ((_v1285(_v1261) == _v142)) {
            _v1292(_v1261);
            _v426 _v1414 = _v1412(_v1261);
            _v1413 = _v541(_v1414);
        }
        _v643(_v977, _v1413);
        _v1294(_v1261, _v195);
        if ((_v1285(_v1261) == _v187)) {
            _v638(_v976, _v1415(_v1261));
            if (((_v1285(_v1261) == _v192) || (_v1285(_v1261) == _v191))) {
                _v1292(_v1261);
            }
        } else {
            _v636(_v976, _v1412(_v1261));
            _v1294(_v1261, _v192);
        }
        _v641(_v621, _v473);
    }
    _v1294(_v1261, _v188);
    return _v1335(_v1261, _v974(_v975, _v621, _v976, _v977), _v339);
}

bkr_i64 _v1416(_v1249 _v1261) {
    return _v1347(_v1417(_v1261));
}

_v426 _v1417(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    bkr_i64 _v1322 = _v1285(_v1261);
    if ((_v1322 == _v151)) {
        return _v1411(_v1261);
    }
    if ((_v1322 == _v142)) {
        _v1292(_v1261);
        _v426 _v1057 = _v1412(_v1261);
        _v429 _v376 = _v1415(_v1261);
        _v426 _v1418 = _v538(_v582(_v376));
        _v1294(_v1261, _v143);
        _v426 _v1419 = _v538(0);
        if ((_v1285(_v1261) == _v142)) {
            _v1419 = _v1417(_v1261);
        } else {
            _v429 _v377 = _v1415(_v1261);
            _v1419 = _v538(_v582(_v377));
        }
        return _v1335(_v1261, _v1056(_v1057, _v1418, _v1419), _v339);
    }
    if ((_v1322 == _v187)) {
        _v429 _v583 = _v1415(_v1261);
        return _v538(_v582(_v583));
    }
    if ((_v1322 == _v132)) {
        bkr_i64 _v1397 = _v1287(_v1261);
        bkr_i64 _v1398 = _v1307(_v1261, _v1397);
        _v1292(_v1261);
        return _v1335(_v1261, _v984(_v1398), _v339);
    }
    if ((_v1322 == _v134)) {
        bkr_i64 _v1420 = _v1287(_v1261);
        _v1292(_v1261);
        return _v1335(_v1261, _v986(_v1309(_v1261, _v1420)), _v339);
    }
    if ((_v1322 == _v135)) {
        _v1292(_v1261);
        return _v1335(_v1261, _v988(1), _v339);
    }
    if ((_v1322 == _v136)) {
        _v1292(_v1261);
        return _v1335(_v1261, _v988(0), _v339);
    }
    if ((_v1322 == _v133)) {
        bkr_i64 _v1420 = _v1287(_v1261);
        _v1292(_v1261);
        return _v1335(_v1261, _v990(_v1309(_v1261, _v1420)), _v339);
    }
    if ((_v1322 == _v185)) {
        _v1292(_v1261);
        if ((_v1285(_v1261) == _v186)) {
            _v1292(_v1261);
            return _v1335(_v1261, _v984(0), _v339);
        }
        _v426 _v542 = _v1412(_v1261);
        if ((_v1285(_v1261) == _v191)) {
            _v1292(_v1261);
            _v426 _v1421 = _v1412(_v1261);
            if ((_v1285(_v1261) == _v191)) {
                _v1292(_v1261);
                _v426 _v1422 = _v1412(_v1261);
                _v1294(_v1261, _v186);
                bkr_i64 _v1423 = vec_new();
                _v434 _v1424 = _v605(_v1423);
                _v636(_v1424, _v542);
                _v636(_v1424, _v1421);
                _v636(_v1424, _v1422);
                bkr_i64 _v1425 = _v1304(_v1261, "bkr_tuple3");
                _v426 _v1426 = _v1015(_v1425, _v1424);
                return _v1335(_v1261, _v1426, _v339);
            }
            _v1294(_v1261, _v186);
            bkr_i64 _v1427 = vec_new();
            _v434 _v1428 = _v605(_v1427);
            _v636(_v1428, _v542);
            _v636(_v1428, _v1421);
            bkr_i64 _v1429 = _v1304(_v1261, "bkr_tuple2");
            _v426 _v1430 = _v1015(_v1429, _v1428);
            return _v1335(_v1261, _v1430, _v339);
        }
        _v1294(_v1261, _v186);
        return _v1335(_v1261, _v542, _v339);
    }
    if ((_v1322 == _v189)) {
        _v1292(_v1261);
        if ((_v1285(_v1261) == _v190)) {
            _v1292(_v1261);
            bkr_i64 _v396 = vec_new();
            _v434 _v995 = _v605(_v396);
            return _v1335(_v1261, _v994(_v995), _v339);
        }
        _v426 _v1431 = _v1412(_v1261);
        if ((_v1285(_v1261) == _v192)) {
            _v1292(_v1261);
            bkr_i64 _v1432 = 0;
            if ((_v1285(_v1261) == _v132)) {
                _v1432 = _v1307(_v1261, _v1287(_v1261));
                _v1292(_v1261);
            } else {
                _v1295(_v1261, _v132);
            }
            _v1294(_v1261, _v190);
            return _v1335(_v1261, _v1000(_v1431, _v1432), _v339);
        }
        bkr_i64 _v396 = vec_new();
        _v434 _v995 = _v605(_v396);
        _v636(_v995, _v1431);
        if ((_v1285(_v1261) == _v191)) {
            _v1292(_v1261);
        }
        while (((_v1285(_v1261) != _v190) && (_v1285(_v1261) != _v129))) {
            _v426 _v1001 = _v1412(_v1261);
            _v636(_v995, _v1001);
            if ((_v1285(_v1261) == _v191)) {
                _v1292(_v1261);
            }
        }
        _v1294(_v1261, _v190);
        return _v1335(_v1261, _v994(_v995), _v339);
    }
    if (_v1323(_v1322)) {
        bkr_i64 _v355 = _v1287(_v1261);
        bkr_str _v1399 = _v1303(_v1261, _v355);
        if (bkr_str_eq(_v1399, "copy")) {
            _v1292(_v1261);
            _v426 _v1032 = _v1417(_v1261);
            return _v1335(_v1261, _v1032, _v339);
        }
        _v1292(_v1261);
        bkr_bool _v1433 = (((bkr_len((bkr_str)(intptr_t)(_v1399)) > 0) && (char_code_at(_v1399, 0) >= 65)) && (char_code_at(_v1399, 0) <= 90));
        bkr_i64 _v1434 = _v1290(_v1261, 1);
        bkr_i64 _v1435 = _v1290(_v1261, 2);
        bkr_bool _v1436 = (((_v1285(_v1261) == _v187) && _v1433) && (((_v1434 == _v188) || (_v1434 == _v182)) || (_v1323(_v1434) && (_v1435 == _v193))));
        if (_v1436) {
            _v1292(_v1261);
            bkr_i64 _v401 = vec_new();
            bkr_i64 _v402 = vec_new();
            _v435 _v1008 = _v612(_v401);
            _v434 _v1009 = _v605(_v402);
            bkr_i64 _v403 = 0;
            while (((_v1285(_v1261) != _v188) && (_v1285(_v1261) != _v129))) {
                if ((_v1285(_v1261) == _v182)) {
                    _v1292(_v1261);
                    _v426 _v1038 = _v1412(_v1261);
                    _v403 = _v541(_v1038);
                    if ((_v1285(_v1261) == _v191)) {
                        _v1292(_v1261);
                    }
                } else {
                    bkr_i64 _v1045 = _v1361(_v1261);
                    _v1294(_v1261, _v193);
                    _v426 _v1437 = _v1412(_v1261);
                    _v643(_v1008, _v1045);
                    _v636(_v1009, _v1437);
                    if ((_v1285(_v1261) == _v191)) {
                        _v1292(_v1261);
                    }
                }
            }
            _v1294(_v1261, _v188);
            return _v1335(_v1261, _v1007(_v355, _v1008, _v1009, _v403), _v339);
        }
        if ((_v1285(_v1261) == _v196)) {
            _v1292(_v1261);
            bkr_i64 _v1438 = _v1361(_v1261);
            bkr_str _v1439 = bkr_str_concat(bkr_str_concat(_v1303(_v1261, _v355), "::"), _v1303(_v1261, _v1438));
            _v355 = _v1304(_v1261, _v1439);
        }
        if ((_v1285(_v1261) == _v185)) {
            _v1292(_v1261);
            bkr_i64 _v356 = vec_new();
            _v434 _v1016 = _v605(_v356);
            while (((_v1285(_v1261) != _v186) && (_v1285(_v1261) != _v129))) {
                _v426 _v1440 = _v1412(_v1261);
                _v636(_v1016, _v1440);
                if ((_v1285(_v1261) == _v191)) {
                    _v1292(_v1261);
                }
            }
            _v1294(_v1261, _v186);
            return _v1335(_v1261, _v1015(_v355, _v1016), _v339);
        }
        return _v1335(_v1261, _v1024(_v355), _v339);
    }
    if ((_v1322 == _v174)) {
        _v1292(_v1261);
        _v426 _v1032 = _v1417(_v1261);
        return _v1335(_v1261, _v1031(_v174, _v1032), _v339);
    }
    if ((_v1322 == _v162)) {
        _v1292(_v1261);
        _v426 _v1032 = _v1417(_v1261);
        return _v1335(_v1261, _v1031(_v162, _v1032), _v339);
    }
    if ((!_v1311(_v1261))) {
        _v1295(_v1261, _v131);
    }
    if ((_v1322 != _v129)) {
        _v1292(_v1261);
    }
    return _v1335(_v1261, _v984(0), _v339);
}

bkr_bool _v1441(_v1249 _v1261) {
    bkr_i64 _v1289 = 1;
    while (BKR_TRUE) {
        bkr_i64 _v1322 = _v1290(_v1261, _v1289);
        if ((_v1322 == _v193)) {
            return BKR_TRUE;
        }
        if (((((((_v1322 == _v192) || (_v1322 == _v188)) || (_v1322 == _v186)) || (_v1322 == _v190)) || (_v1322 == _v191)) || (_v1322 == _v129))) {
            return BKR_FALSE;
        }
        _v1289 = (_v1289 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v1442(_v1249 _v1261) {
    return _v1347(_v1443(_v1261));
}

_v426 _v1443(_v1249 _v1261) {
    _v426 _v1038 = _v1417(_v1261);
    bkr_bool _v1444 = BKR_TRUE;
    while (_v1444) {
        bkr_i64 _v1445 = _v1285(_v1261);
        if ((_v1445 == _v189)) {
            bkr_i64 _v339 = _v546(_v1038);
            _v1292(_v1261);
            _v426 _v1446 = _v1412(_v1261);
            _v1294(_v1261, _v190);
            _v426 _v1039 = _v1037(_v1038, _v1446);
            _v1038 = _v1336(_v1039, _v339, _v1329(_v1261));
        } else {
            if ((_v1445 == _v184)) {
                bkr_i64 _v339 = _v546(_v1038);
                _v1292(_v1261);
                bkr_i64 _v1045 = 0;
                if ((_v1285(_v1261) == _v132)) {
                    bkr_i64 _v1397 = _v1287(_v1261);
                    bkr_i64 _v1398 = _v1307(_v1261, _v1397);
                    _v1292(_v1261);
                    if ((_v1398 == 0)) {
                        _v1045 = _v1304(_v1261, "0");
                    }
                    if ((_v1398 == 1)) {
                        _v1045 = _v1304(_v1261, "1");
                    }
                    if ((_v1398 == 2)) {
                        _v1045 = _v1304(_v1261, "2");
                    }
                    if ((_v1398 == 3)) {
                        _v1045 = _v1304(_v1261, "3");
                    }
                } else {
                    _v1045 = _v1361(_v1261);
                }
                _v426 _v1447 = _v1044(_v1038, _v1045);
                _v1038 = _v1336(_v1447, _v339, _v1329(_v1261));
            } else {
                if ((_v1445 == _v194)) {
                    bkr_bool _v1448 = _v1441(_v1261);
                    if ((!_v1448)) {
                        bkr_i64 _v339 = _v546(_v1038);
                        _v1292(_v1261);
                        _v426 _v1449 = _v1079(_v1038);
                        _v1038 = _v1336(_v1449, _v339, _v1329(_v1261));
                    } else {
                        _v1444 = BKR_FALSE;
                    }
                } else {
                    if ((_v1445 == _v155)) {
                        bkr_i64 _v339 = _v546(_v1038);
                        _v1292(_v1261);
                        _v346 _v1450 = _v1367(_v1261);
                        _v426 _v1451 = _v1085(_v1038, _v1450);
                        _v1038 = _v1336(_v1451, _v339, _v1329(_v1261));
                    } else {
                        _v1444 = BKR_FALSE;
                    }
                }
            }
        }
    }
    if ((_v1285(_v1261) == _v185)) {
        bkr_i64 _v339 = _v546(_v1038);
        bkr_bool _v1452 = BKR_FALSE;
        if ((_v545(_v1038) == _v256)) {
            _v426 _v1453 = _v721(_v1038);
            if ((_v545(_v1453) == _v245)) {
                bkr_str _v1454 = _v1303(_v1261, _v663(_v1453));
                bkr_i64 _v1455 = char_code_at(_v1454, 0);
                if (((_v1455 >= 65) && (_v1455 <= 90))) {
                    _v1452 = BKR_TRUE;
                }
            }
        }
        if (_v1452) {
            _v1292(_v1261);
            if ((_v1285(_v1261) != _v186)) {
                _v426 _v1456 = _v1412(_v1261);
                if ((_v1285(_v1261) == _v191)) {
                    _v1292(_v1261);
                    _v426 _v1457 = _v1412(_v1261);
                    _v1294(_v1261, _v186);
                    _v426 _v1458 = _v984(20);
                    _v426 _v1459 = _v984(8);
                    _v426 _v1460 = _v1050(_v178, _v1456, _v1458);
                    _v426 _v1461 = _v1050(_v178, _v1457, _v1459);
                    _v426 _v1162 = _v1050(_v176, _v1460, _v1461);
                    _v426 _v1462 = _v1050(_v176, _v1162, _v1038);
                    _v1038 = _v1336(_v1462, _v339, _v1329(_v1261));
                } else {
                    _v1294(_v1261, _v186);
                    _v426 _v1459 = _v984(8);
                    _v426 _v1463 = _v1050(_v178, _v1456, _v1459);
                    _v426 _v1462 = _v1050(_v176, _v1463, _v1038);
                    _v1038 = _v1336(_v1462, _v339, _v1329(_v1261));
                }
            } else {
                _v1292(_v1261);
            }
        } else {
            if ((_v545(_v1038) == _v256)) {
                _v426 _v1453 = _v721(_v1038);
                bkr_i64 _v359 = _v723(_v1038);
                _v1292(_v1261);
                bkr_i64 _v1464 = vec_new();
                _v434 _v1016 = _v605(_v1464);
                while (((_v1285(_v1261) != _v186) && (_v1285(_v1261) != _v129))) {
                    _v426 _v1440 = _v1412(_v1261);
                    _v636(_v1016, _v1440);
                    if ((_v1285(_v1261) == _v191)) {
                        _v1292(_v1261);
                    }
                }
                _v1294(_v1261, _v186);
                _v426 _v1465 = _v1021(_v1453, _v359, _v1016);
                _v1038 = _v1336(_v1465, _v339, _v1329(_v1261));
            }
        }
    }
    return _v1038;
}

bkr_i64 _v1466(_v1249 _v1261) {
    return _v1347(_v1467(_v1261));
}

_v426 _v1467(_v1249 _v1261) {
    _v426 _v1051 = _v1443(_v1261);
    while ((((_v1285(_v1261) == _v163) || (_v1285(_v1261) == _v164)) || (_v1285(_v1261) == _v165))) {
        bkr_i64 _v349 = _v1285(_v1261);
        bkr_i64 _v339 = _v546(_v1051);
        _v1292(_v1261);
        _v426 _v1052 = _v1443(_v1261);
        _v426 _v1468 = _v1050(_v349, _v1051, _v1052);
        _v1051 = _v1336(_v1468, _v339, _v548(_v1052));
    }
    return _v1051;
}

bkr_i64 _v1469(_v1249 _v1261) {
    return _v1347(_v1470(_v1261));
}

_v426 _v1470(_v1249 _v1261) {
    _v426 _v1051 = _v1467(_v1261);
    while (((_v1285(_v1261) == _v161) || (_v1285(_v1261) == _v162))) {
        bkr_i64 _v349 = _v1285(_v1261);
        bkr_i64 _v339 = _v546(_v1051);
        _v1292(_v1261);
        _v426 _v1052 = _v1467(_v1261);
        _v426 _v1468 = _v1050(_v349, _v1051, _v1052);
        _v1051 = _v1336(_v1468, _v339, _v548(_v1052));
    }
    return _v1051;
}

bkr_i64 _v1471(_v1249 _v1261) {
    return _v1347(_v1472(_v1261));
}

_v426 _v1472(_v1249 _v1261) {
    _v426 _v1051 = _v1470(_v1261);
    while (((_v1285(_v1261) == _v178) || (_v1285(_v1261) == _v179))) {
        bkr_i64 _v349 = _v1285(_v1261);
        bkr_i64 _v339 = _v546(_v1051);
        _v1292(_v1261);
        _v426 _v1052 = _v1470(_v1261);
        _v426 _v1468 = _v1050(_v349, _v1051, _v1052);
        _v1051 = _v1336(_v1468, _v339, _v548(_v1052));
    }
    return _v1051;
}

bkr_i64 _v1473(_v1249 _v1261) {
    return _v1347(_v1474(_v1261));
}

_v426 _v1474(_v1249 _v1261) {
    _v426 _v1051 = _v1472(_v1261);
    while ((_v1285(_v1261) == _v175)) {
        bkr_i64 _v339 = _v546(_v1051);
        _v1292(_v1261);
        _v426 _v1052 = _v1472(_v1261);
        _v426 _v1468 = _v1050(_v175, _v1051, _v1052);
        _v1051 = _v1336(_v1468, _v339, _v548(_v1052));
    }
    return _v1051;
}

bkr_i64 _v1475(_v1249 _v1261) {
    return _v1347(_v1476(_v1261));
}

_v426 _v1476(_v1249 _v1261) {
    _v426 _v1051 = _v1474(_v1261);
    while ((_v1285(_v1261) == _v177)) {
        bkr_i64 _v339 = _v546(_v1051);
        _v1292(_v1261);
        _v426 _v1052 = _v1474(_v1261);
        _v426 _v1468 = _v1050(_v177, _v1051, _v1052);
        _v1051 = _v1336(_v1468, _v339, _v548(_v1052));
    }
    return _v1051;
}

bkr_i64 _v1477(_v1249 _v1261) {
    return _v1347(_v1478(_v1261));
}

_v426 _v1478(_v1249 _v1261) {
    _v426 _v1051 = _v1476(_v1261);
    while ((_v1285(_v1261) == _v176)) {
        bkr_i64 _v339 = _v546(_v1051);
        _v1292(_v1261);
        _v426 _v1052 = _v1476(_v1261);
        _v426 _v1468 = _v1050(_v176, _v1051, _v1052);
        _v1051 = _v1336(_v1468, _v339, _v548(_v1052));
    }
    return _v1051;
}

bkr_i64 _v1479(_v1249 _v1261) {
    return _v1347(_v1480(_v1261));
}

_v426 _v1480(_v1249 _v1261) {
    _v426 _v1051 = _v1478(_v1261);
    bkr_i64 _v1322 = _v1285(_v1261);
    if (((((((_v1322 == _v166) || (_v1322 == _v167)) || (_v1322 == _v168)) || (_v1322 == _v169)) || (_v1322 == _v170)) || (_v1322 == _v171))) {
        bkr_i64 _v339 = _v546(_v1051);
        _v1292(_v1261);
        _v426 _v1052 = _v1478(_v1261);
        _v426 _v1468 = _v1050(_v1322, _v1051, _v1052);
        return _v1336(_v1468, _v339, _v548(_v1052));
    }
    return _v1051;
}

bkr_i64 _v1481(_v1249 _v1261) {
    return _v1347(_v1482(_v1261));
}

_v426 _v1482(_v1249 _v1261) {
    _v426 _v1051 = _v1480(_v1261);
    while ((_v1285(_v1261) == _v172)) {
        bkr_i64 _v339 = _v546(_v1051);
        _v1292(_v1261);
        _v426 _v1052 = _v1480(_v1261);
        _v426 _v1468 = _v1050(_v172, _v1051, _v1052);
        _v1051 = _v1336(_v1468, _v339, _v548(_v1052));
    }
    return _v1051;
}

bkr_i64 _v1483(_v1249 _v1261) {
    return _v1347(_v1484(_v1261));
}

_v426 _v1484(_v1249 _v1261) {
    _v426 _v1051 = _v1482(_v1261);
    while ((_v1285(_v1261) == _v173)) {
        bkr_i64 _v339 = _v546(_v1051);
        _v1292(_v1261);
        _v426 _v1052 = _v1482(_v1261);
        _v426 _v1468 = _v1050(_v173, _v1051, _v1052);
        _v1051 = _v1336(_v1468, _v339, _v548(_v1052));
    }
    return _v1051;
}

bkr_i64 _v1485(_v1249 _v1261) {
    return _v1347(_v1486(_v1261));
}

_v426 _v1486(_v1249 _v1261) {
    _v426 _v1057 = _v1484(_v1261);
    if ((_v1285(_v1261) == _v194)) {
        _v1292(_v1261);
        _v426 _v1058 = _v1412(_v1261);
        _v1294(_v1261, _v193);
        _v426 _v1059 = _v1412(_v1261);
        _v426 _v1487 = _v1056(_v1057, _v1058, _v1059);
        return _v1336(_v1487, _v546(_v1057), _v548(_v1059));
    }
    return _v1057;
}

bkr_i64 _v1488(_v1249 _v1261) {
    return _v1347(_v1412(_v1261));
}

_v426 _v1412(_v1249 _v1261) {
    _v426 _v542 = _v1486(_v1261);
    while (_v1362(_v1261, "as")) {
        _v1292(_v1261);
        _v1367(_v1261);
    }
    return _v542;
}

bkr_i64 _v1489(_v1249 _v1261) {
    return _v1348(_v1490(_v1261));
}

_v427 _v1490(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1292(_v1261);
    bkr_bool _v1491 = BKR_FALSE;
    if ((_v1285(_v1261) == _v198)) {
        _v1292(_v1261);
        _v1491 = BKR_TRUE;
    }
    bkr_i64 _v355 = _v1361(_v1261);
    bkr_i64 _v516 = _v565();
    if ((_v1285(_v1261) == _v193)) {
        _v1292(_v1261);
        _v516 = _v522(_v1367(_v1261));
    }
    bkr_i64 _v366 = _v565();
    if ((_v1285(_v1261) == _v180)) {
        _v1292(_v1261);
        _v366 = _v543(_v1412(_v1261));
    }
    if ((!_v1294(_v1261, _v192))) {
        _v1355(_v1261);
    }
    _v427 _v1492 = _v1063(_v355, _v516, _v366);
    if (_v1491) {
        _v1064(_v1492);
    }
    return _v1337(_v1261, _v1492, _v339);
}

bkr_i64 _v1493(_v1249 _v1261) {
    return _v1348(_v1494(_v1261));
}

_v427 _v1494(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1292(_v1261);
    bkr_i64 _v368 = _v565();
    if ((_v1285(_v1261) != _v192)) {
        _v368 = _v543(_v1412(_v1261));
    }
    if ((!_v1294(_v1261, _v192))) {
        _v1355(_v1261);
    }
    _v427 _v1495 = _v1070(_v368);
    return _v1337(_v1261, _v1495, _v339);
}

bkr_i64 _v1496(_v1249 _v1261) {
    return _v1348(_v1497(_v1261));
}

_v427 _v1497(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    bkr_i64 _v1322 = _v1285(_v1261);
    if ((_v1322 == _v141)) {
        return _v1490(_v1261);
    }
    if ((_v1322 == _v150)) {
        return _v1494(_v1261);
    }
    if ((_v1322 == _v153)) {
        _v1292(_v1261);
        _v427 _v1498 = _v550(0);
        if ((_v1285(_v1261) == _v187)) {
            _v429 _v583 = _v1415(_v1261);
            _v1498 = _v550(_v582(_v583));
        } else {
            _v426 _v542 = _v1412(_v1261);
            _v1294(_v1261, _v192);
            _v427 _v1499 = _v1103(_v542);
            _v1498 = _v1338(_v1499, _v546(_v542), _v1329(_v1261));
        }
        _v427 _v1500 = _v1074(_v1498);
        return _v1337(_v1261, _v1500, _v339);
    }
    if ((_v1322 == _v147)) {
        _v1292(_v1261);
        _v1294(_v1261, _v192);
        _v427 _v1501 = _v1089();
        return _v1337(_v1261, _v1501, _v339);
    }
    if ((_v1322 == _v148)) {
        _v1292(_v1261);
        _v1294(_v1261, _v192);
        _v427 _v1502 = _v1093();
        return _v1337(_v1261, _v1502, _v339);
    }
    _v426 _v542 = _v1412(_v1261);
    if ((_v1285(_v1261) == _v180)) {
        bkr_i64 _v1503 = _v546(_v542);
        _v1292(_v1261);
        _v426 _v1099 = _v1412(_v1261);
        _v1294(_v1261, _v192);
        _v427 _v1504 = _v1097(_v542, _v1099);
        return _v1338(_v1504, _v1503, _v1329(_v1261));
    }
    if ((!_v1294(_v1261, _v192))) {
        _v1355(_v1261);
    }
    _v427 _v1499 = _v1103(_v542);
    return _v1338(_v1499, _v546(_v542), _v1329(_v1261));
}

bkr_i64 _v1505(_v1249 _v1261) {
    return _v1348(_v1506(_v1261));
}

_v427 _v1506(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1294(_v1261, _v142);
    _v426 _v1057 = _v1412(_v1261);
    _v429 _v1120 = _v1415(_v1261);
    bkr_i64 _v377 = _v565();
    if ((_v1285(_v1261) == _v143)) {
        _v1292(_v1261);
        if ((_v1285(_v1261) == _v142)) {
            _v427 _v1507 = _v1506(_v1261);
            _v377 = _v584(_v1115(_v1507));
        } else {
            _v377 = _v584(_v1415(_v1261));
        }
    }
    _v427 _v1508 = _v1119(_v1057, _v1120, _v377);
    return _v1337(_v1261, _v1508, _v339);
}

bkr_i64 _v1509(_v1249 _v1261) {
    return _v1348(_v1510(_v1261));
}

_v427 _v1510(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1294(_v1261, _v144);
    bkr_i64 _v355 = _v1361(_v1261);
    _v1294(_v1261, _v145);
    _v426 _v1125 = _v1412(_v1261);
    bkr_i64 _v383 = 0;
    if ((_v1285(_v1261) == _v183)) {
        _v383 = 1;
        _v1292(_v1261);
    } else {
        _v1294(_v1261, _v182);
    }
    _v426 _v1126 = _v1412(_v1261);
    _v429 _v1127 = _v1415(_v1261);
    _v427 _v1511 = _v1124(_v355, _v1125, _v1126, _v383, _v1127);
    return _v1337(_v1261, _v1511, _v339);
}

bkr_i64 _v1512(_v1249 _v1261) {
    return _v1350(_v1415(_v1261));
}

_v429 _v1415(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v429 _v583 = _v1107();
    _v1294(_v1261, _v187);
    while (((_v1285(_v1261) != _v188) && (_v1285(_v1261) != _v129))) {
        bkr_i64 _v1322 = _v1285(_v1261);
        if ((_v1322 == _v142)) {
            _v1113(_v583, _v1506(_v1261));
        } else {
            if ((_v1322 == _v144)) {
                _v1113(_v583, _v1510(_v1261));
            } else {
                if ((_v1322 == _v146)) {
                    bkr_i64 _v1513 = _v1328(_v1261);
                    _v1292(_v1261);
                    _v426 _v1057 = _v1412(_v1261);
                    _v429 _v1127 = _v1415(_v1261);
                    _v427 _v1514 = _v1131(_v1057, _v1127);
                    _v1113(_v583, _v1338(_v1514, _v1513, _v1329(_v1261)));
                } else {
                    if ((_v1322 == _v149)) {
                        bkr_i64 _v1513 = _v1328(_v1261);
                        _v1292(_v1261);
                        _v429 _v1127 = _v1415(_v1261);
                        _v427 _v1515 = _v1135(_v1127);
                        _v1113(_v583, _v1338(_v1515, _v1513, _v1329(_v1261)));
                    } else {
                        _v1113(_v583, _v1497(_v1261));
                    }
                }
            }
        }
    }
    _v1294(_v1261, _v188);
    return _v1340(_v1261, _v583, _v339);
}

bkr_i64 _v1516(_v1249 _v1261) {
    return _v1351(_v1517(_v1261));
}

_v434 _v1517(_v1249 _v1261) {
    return _v1518(_v1261, 0);
}

_v434 _v1518(_v1249 _v1261, bkr_i64 _v1519) {
    bkr_i64 _v411 = vec_new();
    _v434 _v1145 = _v605(_v411);
    _v1294(_v1261, _v185);
    if ((_v1285(_v1261) != _v186)) {
        bkr_i64 _v1520 = _v1328(_v1261);
        bkr_i64 _v355 = _v1361(_v1261);
        _v346 _v1521 = _v960(0);
        bkr_str _v1522 = _v1303(_v1261, _v355);
        if ((_v1285(_v1261) == _v193)) {
            _v1292(_v1261);
            _v1521 = _v1367(_v1261);
        } else {
            if ((bkr_str_eq(_v1522, "self") && (_v1519 != 0))) {
                _v1521 = _v964(_v1519);
            }
        }
        _v341 _v1523 = _v1333(_v1140(_v355, _v1521), _v1520, _v1329(_v1261));
        _v635(_v1145, _v1523);
        while ((_v1285(_v1261) == _v191)) {
            _v1292(_v1261);
            if ((_v1285(_v1261) == _v186)) {
                break;
            }
            bkr_i64 _v1524 = _v1328(_v1261);
            bkr_i64 _v1525 = _v1361(_v1261);
            _v1294(_v1261, _v193);
            _v346 _v1526 = _v1367(_v1261);
            _v341 _v1527 = _v1333(_v1140(_v1525, _v1526), _v1524, _v1329(_v1261));
            _v635(_v1145, _v1527);
        }
    }
    _v1294(_v1261, _v186);
    return _v1145;
}

bkr_i64 _v1528(_v1249 _v1261) {
    return _v1349(_v1529(_v1261));
}

_v428 _v1529(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1294(_v1261, _v140);
    bkr_i64 _v355 = _v1361(_v1261);
    bkr_i64 _v1519 = 0;
    if ((_v1285(_v1261) == _v196)) {
        _v1292(_v1261);
        bkr_i64 _v359 = _v1361(_v1261);
        _v1519 = _v355;
        bkr_str _v1439 = bkr_str_concat(bkr_str_concat(_v1303(_v1261, _v355), "::"), _v1303(_v1261, _v359));
        _v355 = _v1304(_v1261, _v1439);
    }
    _v434 _v1145 = _v1518(_v1261, _v1519);
    bkr_i64 _v1146 = _v565();
    if ((_v1285(_v1261) == _v181)) {
        _v1292(_v1261);
        _v1146 = _v522(_v1367(_v1261));
    }
    _v429 _v1127 = _v1415(_v1261);
    _v428 _v1530 = _v1144(_v355, _v1145, _v1146, _v1127);
    return _v1339(_v1261, _v1530, _v339);
}

bkr_i64 _v1531(_v1249 _v1261) {
    return _v1349(_v1532(_v1261));
}

_v428 _v1532(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1294(_v1261, _v152);
    bkr_i64 _v355 = _v1361(_v1261);
    bkr_i64 _v516 = _v565();
    if ((_v1285(_v1261) == _v193)) {
        _v1292(_v1261);
        _v516 = _v522(_v1367(_v1261));
    }
    bkr_i64 _v387 = _v565();
    if ((_v1285(_v1261) == _v180)) {
        _v1292(_v1261);
        _v387 = _v543(_v1412(_v1261));
    }
    if ((!_v1294(_v1261, _v192))) {
        _v1355(_v1261);
    }
    _v428 _v1533 = _v1150(_v355, _v516, _v387);
    return _v1339(_v1261, _v1533, _v339);
}

bkr_i64 _v1534(_v1249 _v1261) {
    return _v1349(_v1535(_v1261));
}

_v428 _v1535(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1294(_v1261, _v138);
    bkr_i64 _v355 = _v1361(_v1261);
    _v1294(_v1261, _v187);
    bkr_i64 _v418 = vec_new();
    _v435 _v1166 = _v612(_v418);
    bkr_i64 _v419 = vec_new();
    _v435 _v1167 = _v612(_v419);
    while (((_v1285(_v1261) != _v188) && (_v1285(_v1261) != _v129))) {
        _v643(_v1166, _v1361(_v1261));
        bkr_i64 _v344 = _v565();
        if ((_v1285(_v1261) == _v185)) {
            _v1292(_v1261);
            bkr_i64 _v416 = vec_new();
            _v435 _v1162 = _v612(_v416);
            _v643(_v1162, _v522(_v1367(_v1261)));
            while ((_v1285(_v1261) == _v191)) {
                _v1292(_v1261);
                _v643(_v1162, _v522(_v1367(_v1261)));
            }
            _v1294(_v1261, _v186);
            _v344 = _v614(_v1162);
        }
        _v643(_v1167, _v344);
        if ((_v1285(_v1261) == _v191)) {
            _v1292(_v1261);
        }
    }
    _v1294(_v1261, _v188);
    return _v1339(_v1261, _v1165(_v355, _v1166, _v1167), _v339);
}

bkr_i64 _v1536(_v1249 _v1261) {
    return _v1349(_v1537(_v1261));
}

_v428 _v1537(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1294(_v1261, _v139);
    bkr_i64 _v355 = _v1361(_v1261);
    bkr_i64 _v416 = vec_new();
    _v434 _v1162 = _v605(_v416);
    if ((_v1285(_v1261) == _v185)) {
        _v1292(_v1261);
        bkr_i64 _v1036 = 0;
        while (((_v1285(_v1261) != _v186) && (_v1285(_v1261) != _v129))) {
            bkr_i64 _v1538 = _v1328(_v1261);
            _v346 _v1156 = _v1367(_v1261);
            bkr_i64 _v1045 = _v1304(_v1261, int_to_string(_v1036));
            _v341 _v1447 = _v1333(_v1155(_v1045, _v1156), _v1538, _v1329(_v1261));
            _v635(_v1162, _v1447);
            _v1036 = (_v1036 + 1);
            if ((_v1285(_v1261) == _v191)) {
                _v1292(_v1261);
            }
        }
        _v1294(_v1261, _v186);
        if ((_v1285(_v1261) == _v192)) {
            _v1292(_v1261);
        }
    } else {
        _v1294(_v1261, _v187);
        while (((_v1285(_v1261) != _v188) && (_v1285(_v1261) != _v129))) {
            bkr_i64 _v1538 = _v1328(_v1261);
            bkr_i64 _v1045 = _v1361(_v1261);
            _v1294(_v1261, _v193);
            _v346 _v1156 = _v1367(_v1261);
            _v341 _v1447 = _v1333(_v1155(_v1045, _v1156), _v1538, _v1329(_v1261));
            _v635(_v1162, _v1447);
            if ((_v1285(_v1261) == _v191)) {
                _v1292(_v1261);
            }
        }
        _v1294(_v1261, _v188);
    }
    _v428 _v1539 = _v1161(_v355, _v1162);
    return _v1339(_v1261, _v1539, _v339);
}

bkr_i64 _v1540(bkr_i64 _v1261) {
    return _v1541(_v1258(_v1261));
}

bkr_i64 _v1542(_v1249 _v1261) {
    return _v1349(_v1543(_v1261));
}

_v428 _v1543(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1294(_v1261, _v154);
    bkr_i64 _v355 = _v1361(_v1261);
    _v1294(_v1261, _v180);
    _v346 _v373 = _v1367(_v1261);
    if ((!_v1294(_v1261, _v192))) {
        _v1355(_v1261);
    }
    _v428 _v1544 = _v1178(_v355, _v373);
    return _v1339(_v1261, _v1544, _v339);
}

bkr_i64 _v1541(_v1249 _v1261) {
    bkr_i64 _v339 = _v1328(_v1261);
    _v1294(_v1261, _v137);
    bkr_i64 _v355 = _v1361(_v1261);
    _v1294(_v1261, _v187);
    bkr_i64 _v423 = vec_new();
    _v434 _v1186 = _v605(_v423);
    bkr_i64 _v1187 = (-1);
    while (((_v1285(_v1261) != _v188) && (_v1285(_v1261) != _v129))) {
        bkr_i64 _v1322 = _v1285(_v1261);
        if ((_v1322 == _v197)) {
            _v1292(_v1261);
            _v1322 = _v1285(_v1261);
        }
        if ((_v1322 == _v140)) {
            _v428 _v1530 = _v1529(_v1261);
            bkr_i64 _v1545 = _v869(_v1530);
            if (bkr_str_eq(_v1303(_v1261, _v1545), "main")) {
                _v1187 = _v1545;
            }
            _v637(_v1186, _v1530);
        } else {
            if ((_v1322 == _v152)) {
                _v637(_v1186, _v1532(_v1261));
            } else {
                if ((_v1322 == _v139)) {
                    _v637(_v1186, _v1537(_v1261));
                } else {
                    if ((_v1322 == _v138)) {
                        _v637(_v1186, _v1535(_v1261));
                    } else {
                        if ((_v1322 == _v154)) {
                            _v637(_v1186, _v1543(_v1261));
                        } else {
                            _v1295(_v1261, _v140);
                            _v1292(_v1261);
                            _v1356(_v1261);
                        }
                    }
                }
            }
        }
    }
    _v1294(_v1261, _v188);
    _v437 _v1188 = _v625(_v1264(_v1261));
    _v341 _v1546 = _v1185(_v355, _v1186, _v1187, _v1188);
    return _v1342(_v1332(_v1261, _v1546, _v339));
}

bkr_i64 _v1548(bkr_str _v1549, bkr_i64 _v425) {
    return _v1550(_v1551(_v1549, _v425));
}

_v1547 _v1551(bkr_str _v1549, bkr_i64 _v425) {
    bkr_i64 _v1254 = vec_new();
    bkr_i64 _v1552 = vec_new();
    bkr_i64 _v1553 = vec_new();
    bkr_i64 _v1554 = vec_new();
    bkr_i64 _v1555 = vec_new();
    bkr_i64 _v1556 = vec_new();
    bkr_i64 _v1557 = vec_new();
    bkr_i64 _v1558 = vec_new();
    bkr_i64 _v1559 = vec_new();
    bkr_i64 _v1560 = vec_new();
    bkr_i64 _v1561 = vec_new();
    vec_push(_v1254, ((bkr_i64)(_v1552)));
    vec_push(_v1254, 0);
    vec_push(_v1254, ((bkr_i64)(_v1549)));
    vec_push(_v1254, ((bkr_i64)(_v425)));
    vec_push(_v1254, ((bkr_i64)(_v1553)));
    vec_push(_v1254, ((bkr_i64)(_v1554)));
    vec_push(_v1254, ((bkr_i64)(_v1555)));
    vec_push(_v1254, ((bkr_i64)(_v1556)));
    vec_push(_v1254, ((bkr_i64)(_v1557)));
    vec_push(_v1254, ((bkr_i64)(_v1558)));
    vec_push(_v1254, ((bkr_i64)(_v1559)));
    vec_push(_v1254, ((bkr_i64)(_v1560)));
    bkr_i64 _v1562 = vec_new();
    bkr_i64 _v1563 = vec_new();
    vec_push(_v1254, ((bkr_i64)(_v1561)));
    vec_push(_v1254, 0);
    vec_push(_v1254, 0);
    vec_push(_v1254, ((bkr_i64)(_v1562)));
    vec_push(_v1254, 0);
    vec_push(_v1254, ((bkr_i64)(_v1563)));
    return _v1564(_v1254);
}

_v1547 _v1565(_v1547 _v1566, bkr_i64 _v1567) {
    bkr_i64 _v1254 = _v1550(_v1566);
    if ((vec_len(_v1254) < 14)) {
        vec_push(_v1254, _v1567);
    } else {
        vec_set(_v1254, 13, _v1567);
    }
    return _v1566;
}

bkr_i64 _v1568(_v1547 _v1566) {
    bkr_i64 _v1254 = _v1550(_v1566);
    if ((vec_len(_v1254) < 14)) {
        return 0;
    }
    return vec_get(_v1254, 13);
}

_v1547 _v1564(bkr_i64 _v1254) {
    return (_v1547){._v342 = ((bkr_i64)(_v1254))};
}

bkr_i64 _v1550(_v1547 _v1566) {
    return ((bkr_i64)(_v1566._v342));
}

bkr_i64 _v1569(bkr_i64 _v1254) {
    return _v1570(_v1564(_v1254));
}

bkr_i64 _v1570(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 0)));
}

bkr_i64 _v1571(bkr_i64 _v1254) {
    return _v1572(_v1564(_v1254));
}

bkr_i64 _v1572(_v1547 _v1566) {
    return vec_get(_v1550(_v1566), 1);
}

bkr_i64 _v1573(bkr_i64 _v1254, bkr_i64 _v1574) {
    _v1575(_v1564(_v1254), _v1574);
    return _v1254;
}

_v1547 _v1575(_v1547 _v1566, bkr_i64 _v1574) {
    vec_set(_v1550(_v1566), 1, _v1574);
    return _v1566;
}

bkr_i64 _v1576(bkr_i64 _v1254) {
    return _v1577(_v1564(_v1254));
}

bkr_i64 _v1577(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 3)));
}

bkr_i64 _v1578(_v1547 _v1566, bkr_str _v1305) {
    bkr_i64 _v425 = _v1577(_v1566);
    bkr_i64 _v1172 = 0;
    bkr_i64 _v399 = vec_len(_v425);
    while ((_v1172 < _v399)) {
        if (bkr_str_eq(vec_get(_v425, _v1172), _v1305)) {
            return _v1172;
        }
        _v1172 = (_v1172 + 1);
    }
    vec_push(_v425, ((bkr_i64)(intptr_t)_v1305));
    return _v399;
}

bkr_i64 _v1579(bkr_i64 _v1254) {
    return _v1580(_v1564(_v1254));
}

bkr_i64 _v1580(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 4)));
}

bkr_i64 _v1581(bkr_i64 _v1254) {
    return _v1582(_v1564(_v1254));
}

bkr_i64 _v1582(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 5)));
}

bkr_i64 _v1583(bkr_i64 _v1254) {
    return _v1584(_v1564(_v1254));
}

bkr_i64 _v1584(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 6)));
}

bkr_i64 _v1585(bkr_i64 _v1254) {
    return _v1586(_v1564(_v1254));
}

bkr_i64 _v1586(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 7)));
}

bkr_i64 _v1587(bkr_i64 _v1254) {
    return _v1588(_v1564(_v1254));
}

bkr_i64 _v1588(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 8)));
}

bkr_i64 _v1589(bkr_i64 _v1254) {
    return _v1590(_v1564(_v1254));
}

bkr_i64 _v1590(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 9)));
}

bkr_i64 _v1591(bkr_i64 _v1254) {
    return _v1592(_v1564(_v1254));
}

bkr_i64 _v1592(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 10)));
}

bkr_i64 _v1593(bkr_i64 _v1254) {
    return _v1594(_v1564(_v1254));
}

bkr_i64 _v1594(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 11)));
}

bkr_i64 _v1595(bkr_i64 _v1254) {
    return _v1596(_v1564(_v1254));
}

bkr_i64 _v1596(_v1547 _v1566) {
    return ((bkr_i64)(vec_get(_v1550(_v1566), 12)));
}

bkr_i64 _v1597(bkr_i64 _v1254, bkr_str _v1598) {
    _v1599(_v1564(_v1254), _v1598);
    return _v1254;
}

_v1547 _v1599(_v1547 _v1566, bkr_str _v1598) {
    bkr_i64 _v1552 = _v1570(_v1566);
    bkr_i64 _v1574 = _v1572(_v1566);
    bkr_str _v1600 = "";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v1574)) {
        _v1600 = bkr_str_concat(_v1600, "    ");
        _v1172 = (_v1172 + 1);
    }
    vec_push(_v1552, ((bkr_i64)(intptr_t)bkr_str_concat(_v1600, _v1598)));
    return _v1566;
}

bkr_i64 _v1601(bkr_i64 _v1254) {
    _v1602(_v1564(_v1254));
    return _v1254;
}

_v1547 _v1602(_v1547 _v1566) {
    _v1575(_v1566, (_v1572(_v1566) + 1));
    return _v1566;
}

bkr_i64 _v1603(bkr_i64 _v1254) {
    _v1604(_v1564(_v1254));
    return _v1254;
}

_v1547 _v1604(_v1547 _v1566) {
    _v1575(_v1566, (_v1572(_v1566) - 1));
    return _v1566;
}

bkr_i64 _v1605(bkr_i64 _v1254) {
    _v1606(_v1564(_v1254));
    return _v1254;
}

_v1547 _v1606(_v1547 _v1566) {
    bkr_i64 _v1254 = _v1550(_v1566);
    bkr_i64 _v1553 = vec_new();
    bkr_i64 _v1554 = vec_new();
    bkr_i64 _v1559 = vec_new();
    bkr_i64 _v1560 = vec_new();
    bkr_i64 _v1561 = vec_new();
    bkr_i64 _v1562 = vec_new();
    bkr_i64 _v1563 = vec_new();
    vec_set(_v1254, 4, ((bkr_i64)(_v1553)));
    vec_set(_v1254, 5, ((bkr_i64)(_v1554)));
    vec_set(_v1254, 10, ((bkr_i64)(_v1559)));
    vec_set(_v1254, 11, ((bkr_i64)(_v1560)));
    vec_set(_v1254, 12, ((bkr_i64)(_v1561)));
    if ((vec_len(_v1254) > 15)) {
        vec_set(_v1254, 15, ((bkr_i64)(_v1562)));
    }
    if ((vec_len(_v1254) > 17)) {
        vec_set(_v1254, 17, ((bkr_i64)(_v1563)));
    }
    return _v1566;
}

bkr_i64 _v1607(bkr_i64 _v1254, bkr_i64 _v355, bkr_i64 _v319) {
    _v1608(_v1564(_v1254), _v355, _v319);
    return _v1254;
}

_v1547 _v1608(_v1547 _v1566, bkr_i64 _v355, bkr_i64 _v319) {
    bkr_i64 _v1553 = _v1580(_v1566);
    bkr_i64 _v1554 = _v1582(_v1566);
    bkr_i64 _v1563 = _v1609(_v1566);
    vec_push(_v1553, _v355);
    vec_push(_v1554, _v319);
    vec_push(_v1563, (-1));
    return _v1566;
}

_v1547 _v1610(_v1547 _v1566, bkr_i64 _v355, bkr_i64 _v319, bkr_i64 _v1519) {
    _v1608(_v1566, _v355, _v319);
    bkr_i64 _v1563 = _v1609(_v1566);
    vec_set(_v1563, (vec_len(_v1563) - 1), _v1519);
    return _v1566;
}

bkr_i64 _v1609(_v1547 _v1566) {
    bkr_i64 _v1254 = _v1550(_v1566);
    if ((vec_len(_v1254) <= 17)) {
        bkr_i64 _v1611 = vec_new();
        return _v1611;
    }
    return ((bkr_i64)(vec_get(_v1254, 17)));
}

bkr_i64 _v1612(_v1547 _v1566, bkr_i64 _v355) {
    bkr_i64 _v1553 = _v1580(_v1566);
    bkr_i64 _v1563 = _v1609(_v1566);
    bkr_i64 _v1172 = (vec_len(_v1553) - 1);
    while ((_v1172 >= 0)) {
        if ((vec_get(_v1553, _v1172) == _v355)) {
            if ((_v1172 < vec_len(_v1563))) {
                return vec_get(_v1563, _v1172);
            }
            return (-1);
        }
        _v1172 = (_v1172 - 1);
    }
    return (-1);
}

bkr_i64 _v1613(_v1547 _v1566) {
    bkr_i64 _v1254 = _v1550(_v1566);
    if ((vec_len(_v1254) <= 15)) {
        bkr_i64 _v1562 = vec_new();
        return _v1562;
    }
    return ((bkr_i64)(vec_get(_v1254, 15)));
}

_v1547 _v1614(_v1547 _v1566, bkr_i64 _v1615) {
    bkr_i64 _v1562 = _v1613(_v1566);
    vec_push(_v1562, _v1615);
    return _v1566;
}

bkr_str _v1616(_v1547 _v1566) {
    bkr_i64 _v1254 = _v1550(_v1566);
    if ((vec_len(_v1254) <= 14)) {
        return "bkr_i64";
    }
    bkr_i64 _v1398 = vec_get(_v1254, 14);
    if ((_v1398 == 0)) {
        return "bkr_i64";
    }
    return ((bkr_str)(_v1398));
}

_v1547 _v1617(_v1547 _v1566, bkr_str _v1146) {
    bkr_i64 _v1254 = _v1550(_v1566);
    if ((vec_len(_v1254) > 14)) {
        vec_set(_v1254, 14, ((bkr_i64)(_v1146)));
    }
    return _v1566;
}

bkr_i64 _v1618(_v1547 _v1566) {
    bkr_i64 _v1254 = _v1550(_v1566);
    if ((vec_len(_v1254) <= 16)) {
        return 0;
    }
    bkr_i64 _v1619 = vec_get(_v1254, 16);
    vec_set(_v1254, 16, (_v1619 + 1));
    return _v1619;
}

bkr_str _v1620(_v1547 _v1566, bkr_str _v1600) {
    bkr_i64 _v1621 = _v1618(_v1566);
    return bkr_str_concat(bkr_str_concat(_v1600, "_"), int_to_string(_v1621));
}

bkr_i64 _v1622(bkr_i64 _v1254, bkr_i64 _v355, bkr_i64 _v319) {
    _v1623(_v1564(_v1254), _v355, _v319);
    return _v1254;
}

_v1547 _v1623(_v1547 _v1566, bkr_i64 _v355, bkr_i64 _v319) {
    bkr_i64 _v1555 = _v1584(_v1566);
    bkr_i64 _v1556 = _v1586(_v1566);
    vec_push(_v1555, _v355);
    vec_push(_v1556, _v319);
    return _v1566;
}

bkr_i64 _v1624(bkr_i64 _v1254, bkr_i64 _v355, bkr_i64 _v319) {
    _v1625(_v1564(_v1254), _v355, _v319);
    return _v1254;
}

_v1547 _v1625(_v1547 _v1566, bkr_i64 _v355, bkr_i64 _v319) {
    bkr_i64 _v1557 = _v1588(_v1566);
    bkr_i64 _v1558 = _v1590(_v1566);
    vec_push(_v1557, _v355);
    vec_push(_v1558, _v319);
    return _v1566;
}

bkr_i64 _v1626(bkr_i64 _v1254, bkr_i64 _v355, bkr_i64 _v954, bkr_i64 _v955) {
    _v1627(_v1564(_v1254), _v355, _v954, _v955);
    return _v1254;
}

_v1547 _v1627(_v1547 _v1566, bkr_i64 _v355, bkr_i64 _v954, bkr_i64 _v955) {
    bkr_i64 _v1559 = _v1592(_v1566);
    bkr_i64 _v1560 = _v1594(_v1566);
    bkr_i64 _v1561 = _v1596(_v1566);
    vec_push(_v1559, _v355);
    vec_push(_v1560, _v955);
    vec_push(_v1561, _v954);
    return _v1566;
}

bkr_i64 _v1628(bkr_i64 _v1254, bkr_i64 _v355) {
    return _v1629(_v1564(_v1254), _v355);
}

bkr_i64 _v1629(_v1547 _v1566, bkr_i64 _v355) {
    bkr_i64 _v1559 = _v1592(_v1566);
    bkr_i64 _v1560 = _v1594(_v1566);
    bkr_i64 _v1196 = (-1);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v1559))) {
        if ((vec_get(_v1559, _v1172) == _v355)) {
            _v1196 = vec_get(_v1560, _v1172);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1196;
}

bkr_i64 _v1630(bkr_i64 _v1254, bkr_i64 _v355) {
    return _v1631(_v1564(_v1254), _v355);
}

bkr_i64 _v1631(_v1547 _v1566, bkr_i64 _v355) {
    bkr_i64 _v1559 = _v1592(_v1566);
    bkr_i64 _v1561 = _v1596(_v1566);
    bkr_i64 _v1196 = _v316;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v1559))) {
        if ((vec_get(_v1559, _v1172) == _v355)) {
            _v1196 = vec_get(_v1561, _v1172);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1196;
}

bkr_i64 _v1632(bkr_i64 _v425, bkr_i64 _v1633, bkr_i64 _v355) {
    bkr_i64 _v1196 = _v316;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v425))) {
        if ((vec_get(_v425, _v1172) == _v355)) {
            _v1196 = vec_get(_v1633, _v1172);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1196;
}

bkr_i64 _v1634(bkr_i64 _v1254, bkr_i64 _v355) {
    return _v1635(_v1564(_v1254), _v355);
}

bkr_i64 _v1635(_v1547 _v1566, bkr_i64 _v355) {
    bkr_i64 _v1636 = _v1632(_v1580(_v1566), _v1582(_v1566), _v355);
    if ((_v1636 != _v316)) {
        return _v1636;
    }
    return _v1632(_v1588(_v1566), _v1590(_v1566), _v355);
}

bkr_i64 _v1637(bkr_i64 _v1254, bkr_i64 _v355) {
    return _v1638(_v1564(_v1254), _v355);
}

bkr_i64 _v1638(_v1547 _v1566, bkr_i64 _v355) {
    return _v1632(_v1584(_v1566), _v1586(_v1566), _v355);
}

bkr_bool _v1639(_v1547 _v1254, bkr_i64 _v355) {
    bkr_i64 _v425 = _v1577(_v1254);
    return _v1640(_v1254, _v1641(_v425, _v355));
}

bkr_bool _v1640(_v1547 _v1254, bkr_str _v1642) {
    bkr_i64 _v1567 = _v1568(_v1254);
    if ((_v1567 == 0)) {
        return BKR_FALSE;
    }
    _v341 _v1546 = _v507(_v1567);
    bkr_i64 _v425 = _v1577(_v1254);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v259)) {
            if (bkr_str_eq(_v1641(_v425, _v1168(_v563)), _v1642)) {
                return BKR_TRUE;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v1643(_v1547 _v1254, bkr_str _v1642, bkr_str _v1644) {
    bkr_i64 _v1567 = _v1568(_v1254);
    if ((_v1567 == 0)) {
        return (-1);
    }
    _v341 _v1546 = _v507(_v1567);
    bkr_i64 _v425 = _v1577(_v1254);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v259)) {
            if (bkr_str_eq(_v1641(_v425, _v1168(_v563)), _v1642)) {
                _v435 _v1166 = _v1169(_v563);
                bkr_i64 _v1645 = 0;
                while ((_v1645 < _v916(_v1166))) {
                    if (bkr_str_eq(_v1641(_v425, _v918(_v1166, _v1645)), _v1644)) {
                        return _v1645;
                    }
                    _v1645 = (_v1645 + 1);
                }
                return (-1);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return (-1);
}

bkr_i64 _v1646(_v1547 _v1254, bkr_str _v1642, bkr_str _v1644, bkr_i64 _v1647) {
    bkr_i64 _v1567 = _v1568(_v1254);
    if ((_v1567 == 0)) {
        return _v316;
    }
    _v341 _v1546 = _v507(_v1567);
    bkr_i64 _v425 = _v1577(_v1254);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v259)) {
            if (bkr_str_eq(_v1641(_v425, _v1168(_v563)), _v1642)) {
                _v435 _v1166 = _v1169(_v563);
                _v435 _v1167 = _v1170(_v563);
                bkr_i64 _v1645 = 0;
                while ((_v1645 < _v916(_v1166))) {
                    if (bkr_str_eq(_v1641(_v425, _v918(_v1166, _v1645)), _v1644)) {
                        if ((_v1645 < _v916(_v1167))) {
                            bkr_i64 _v344 = _v918(_v1167, _v1645);
                            if (_v526(_v344)) {
                                _v435 _v1162 = _v611(_v344);
                                if (((_v1647 >= 0) && (_v1647 < _v916(_v1162)))) {
                                    bkr_i64 _v1648 = _v918(_v1162, _v1647);
                                    if (_v526(_v1648)) {
                                        return _v530(_v517(_v1648));
                                    }
                                }
                            }
                        }
                        return _v316;
                    }
                    _v1645 = (_v1645 + 1);
                }
                return _v316;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v316;
}

bkr_bool _v1649(_v1547 _v1254, bkr_str _v1642) {
    bkr_i64 _v1567 = _v1568(_v1254);
    if ((_v1567 == 0)) {
        return BKR_FALSE;
    }
    _v341 _v1546 = _v507(_v1567);
    bkr_i64 _v425 = _v1577(_v1254);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v259)) {
            if (bkr_str_eq(_v1641(_v425, _v1168(_v563)), _v1642)) {
                _v435 _v1167 = _v1170(_v563);
                bkr_i64 _v1645 = 0;
                while ((_v1645 < _v916(_v1167))) {
                    bkr_i64 _v344 = _v918(_v1167, _v1645);
                    if (_v526(_v344)) {
                        _v435 _v1162 = _v611(_v344);
                        bkr_i64 _v574 = 0;
                        while ((_v574 < _v916(_v1162))) {
                            bkr_i64 _v1648 = _v918(_v1162, _v574);
                            if (_v526(_v1648)) {
                                if ((_v530(_v517(_v1648)) == _v306)) {
                                    return BKR_TRUE;
                                }
                            }
                            _v574 = (_v574 + 1);
                        }
                    }
                    _v1645 = (_v1645 + 1);
                }
                return BKR_FALSE;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_str _v1650(bkr_i64 _v319) {
    if ((_v319 == _v302)) {
        return "bkr_i32";
    }
    if ((_v319 == _v303)) {
        return "bkr_i64";
    }
    if ((_v319 == _v304)) {
        return "bkr_f64";
    }
    if ((_v319 == _v305)) {
        return "bkr_bool";
    }
    if ((_v319 == _v306)) {
        return "bkr_str";
    }
    if (((_v319 == _v307) || (_v319 == _v314))) {
        return "void";
    }
    if ((((((_v319 == _v310) || (_v319 == _v311)) || (_v319 == _v312)) || (_v319 == _v313)) || (_v319 == _v315))) {
        return "bkr_i64";
    }
    return "bkr_i64";
}

bkr_str _v1651(bkr_i64 _v1254, bkr_i64 _v516) {
    if (_v524(_v516)) {
        return "bkr_i64";
    }
    return _v1652(_v1564(_v1254), _v517(_v516));
}

bkr_str _v1652(_v1547 _v1254, _v346 _v521) {
    bkr_i64 _v319 = _v530(_v521);
    if ((_v319 == _v308)) {
        bkr_i64 _v954 = _v533(_v521);
        return bkr_str_concat(_v1650(_v954), "*");
    }
    if ((_v319 == _v309)) {
        bkr_i64 _v1519 = _v532(_v521);
        if ((_v1519 >= 0)) {
            if (_v1639(_v1254, _v1519)) {
                return "bkr_i64";
            }
            return _v1653(_v1254, _v1519);
        }
    }
    return _v1650(_v319);
}

bkr_str _v1654(bkr_i64 _v349) {
    if ((_v349 == _v161)) {
        return " + ";
    }
    if ((_v349 == _v162)) {
        return " - ";
    }
    if ((_v349 == _v163)) {
        return " * ";
    }
    if ((_v349 == _v164)) {
        return " / ";
    }
    if ((_v349 == _v165)) {
        return " % ";
    }
    if ((_v349 == _v166)) {
        return " == ";
    }
    if ((_v349 == _v167)) {
        return " != ";
    }
    if ((_v349 == _v168)) {
        return " < ";
    }
    if ((_v349 == _v169)) {
        return " > ";
    }
    if ((_v349 == _v170)) {
        return " <= ";
    }
    if ((_v349 == _v171)) {
        return " >= ";
    }
    if ((_v349 == _v172)) {
        return " && ";
    }
    if ((_v349 == _v173)) {
        return " || ";
    }
    if ((_v349 == _v175)) {
        return " & ";
    }
    if ((_v349 == _v176)) {
        return " | ";
    }
    if ((_v349 == _v177)) {
        return " ^ ";
    }
    if ((_v349 == _v178)) {
        return " << ";
    }
    if ((_v349 == _v179)) {
        return " >> ";
    }
    return " ? ";
}

bkr_str _v1641(bkr_i64 _v425, bkr_i64 _v1036) {
    if (((_v1036 >= 0) && (_v1036 < vec_len(_v425)))) {
        return vec_get(_v425, _v1036);
    }
    return "";
}

bkr_str _v1655(bkr_str _v1656) {
    if (bkr_str_eq(_v1656, "len")) {
        return "bkr_len";
    }
    if (bkr_str_eq(_v1656, "strlen")) {
        return "bkr_len";
    }
    if (bkr_str_eq(_v1656, "print")) {
        return "bkr_print";
    }
    if (bkr_str_eq(_v1656, "println")) {
        return "bkr_println";
    }
    if (bkr_str_eq(_v1656, "log")) {
        return "bkr_log";
    }
    if (bkr_str_eq(_v1656, "read_file")) {
        return "read_file";
    }
    if (bkr_str_eq(_v1656, "write_file")) {
        return "write_file";
    }
    if (bkr_str_eq(_v1656, "file_exists")) {
        return "file_exists";
    }
    if (bkr_str_eq(_v1656, "file_set_executable")) {
        return "file_set_executable";
    }
    if (bkr_str_eq(_v1656, "vec_new")) {
        return "vec_new";
    }
    if (bkr_str_eq(_v1656, "vec_push")) {
        return "vec_push";
    }
    if (bkr_str_eq(_v1656, "vec_get")) {
        return "vec_get";
    }
    if (bkr_str_eq(_v1656, "vec_set")) {
        return "vec_set";
    }
    if (bkr_str_eq(_v1656, "vec_len")) {
        return "vec_len";
    }
    if (bkr_str_eq(_v1656, "vec_pop")) {
        return "vec_pop";
    }
    if (bkr_str_eq(_v1656, "vec_clear")) {
        return "vec_clear";
    }
    if (bkr_str_eq(_v1656, "vec_contains")) {
        return "vec_contains";
    }
    if (bkr_str_eq(_v1656, "vec_is_empty")) {
        return "vec_is_empty";
    }
    if (bkr_str_eq(_v1656, "vec_clone")) {
        return "vec_clone";
    }
    if (bkr_str_eq(_v1656, "vec_reverse")) {
        return "vec_reverse";
    }
    if (bkr_str_eq(_v1656, "hashmap_is_empty")) {
        return "hashmap_is_empty";
    }
    if (bkr_str_eq(_v1656, "hashmap_values")) {
        return "hashmap_values";
    }
    if (bkr_str_eq(_v1656, "vec_map")) {
        return "vec_map";
    }
    if (bkr_str_eq(_v1656, "vec_filter")) {
        return "vec_filter";
    }
    if (bkr_str_eq(_v1656, "vec_fold")) {
        return "vec_fold";
    }
    if (bkr_str_eq(_v1656, "vec_find")) {
        return "vec_find";
    }
    if (bkr_str_eq(_v1656, "hashmap_new")) {
        return "hashmap_new";
    }
    if (bkr_str_eq(_v1656, "hashmap_insert")) {
        return "hashmap_insert";
    }
    if (bkr_str_eq(_v1656, "hashmap_get")) {
        return "hashmap_get";
    }
    if (bkr_str_eq(_v1656, "hashmap_contains")) {
        return "hashmap_contains";
    }
    if (bkr_str_eq(_v1656, "hashmap_remove")) {
        return "hashmap_remove";
    }
    if (bkr_str_eq(_v1656, "hashmap_keys")) {
        return "hashmap_keys";
    }
    if (bkr_str_eq(_v1656, "hashmap_len")) {
        return "hashmap_len";
    }
    if (bkr_str_eq(_v1656, "hashmap_clear")) {
        return "hashmap_clear";
    }
    if (bkr_str_eq(_v1656, "char_at")) {
        return "char_at";
    }
    if (bkr_str_eq(_v1656, "char_code")) {
        return "char_code";
    }
    if (bkr_str_eq(_v1656, "char_code_at")) {
        return "char_code_at";
    }
    if (bkr_str_eq(_v1656, "substring")) {
        return "substring";
    }
    if (bkr_str_eq(_v1656, "contains")) {
        return "contains";
    }
    if (bkr_str_eq(_v1656, "starts_with")) {
        return "starts_with";
    }
    if (bkr_str_eq(_v1656, "ends_with")) {
        return "ends_with";
    }
    if (bkr_str_eq(_v1656, "trim")) {
        return "trim";
    }
    if (bkr_str_eq(_v1656, "parse_int")) {
        return "parse_int";
    }
    if (bkr_str_eq(_v1656, "int_to_string")) {
        return "int_to_string";
    }
    if (bkr_str_eq(_v1656, "from_char_code")) {
        return "from_char_code";
    }
    if (bkr_str_eq(_v1656, "join_lines")) {
        return "join_lines";
    }
    if (bkr_str_eq(_v1656, "args_count")) {
        return "bkr_args_count";
    }
    if (bkr_str_eq(_v1656, "arg_at")) {
        return "bkr_arg_at";
    }
    if (bkr_str_eq(_v1656, "str_index_of")) {
        return "str_index_of";
    }
    if (bkr_str_eq(_v1656, "str_replace")) {
        return "str_replace";
    }
    if (bkr_str_eq(_v1656, "str_split")) {
        return "str_split";
    }
    if (bkr_str_eq(_v1656, "str_to_upper")) {
        return "str_to_upper";
    }
    if (bkr_str_eq(_v1656, "str_to_lower")) {
        return "str_to_lower";
    }
    if (bkr_str_eq(_v1656, "str_repeat")) {
        return "str_repeat";
    }
    if (bkr_str_eq(_v1656, "path_join")) {
        return "path_join";
    }
    if (bkr_str_eq(_v1656, "path_dir")) {
        return "path_dir";
    }
    if (bkr_str_eq(_v1656, "path_base")) {
        return "path_base";
    }
    if (bkr_str_eq(_v1656, "path_ext")) {
        return "path_ext";
    }
    if (bkr_str_eq(_v1656, "path_is_abs")) {
        return "path_is_abs";
    }
    if (bkr_str_eq(_v1656, "env_var")) {
        return "env_var";
    }
    if (bkr_str_eq(_v1656, "env_get")) {
        return "env_get";
    }
    if (bkr_str_eq(_v1656, "env_set")) {
        return "env_set";
    }
    if (bkr_str_eq(_v1656, "env_has")) {
        return "env_has";
    }
    if (bkr_str_eq(_v1656, "time_now_ms")) {
        return "time_now_ms";
    }
    if (bkr_str_eq(_v1656, "time_now_unix")) {
        return "time_now_unix";
    }
    if (bkr_str_eq(_v1656, "runtime_version_major")) {
        return "runtime_version_major";
    }
    if (bkr_str_eq(_v1656, "runtime_version_minor")) {
        return "runtime_version_minor";
    }
    if (bkr_str_eq(_v1656, "runtime_version_patch")) {
        return "runtime_version_patch";
    }
    if (bkr_str_eq(_v1656, "runtime_version_str")) {
        return "runtime_version_str";
    }
    if (bkr_str_eq(_v1656, "bytes_new")) {
        return "bytes_new";
    }
    if (bkr_str_eq(_v1656, "bytes_len")) {
        return "bytes_len";
    }
    if (bkr_str_eq(_v1656, "bytes_capacity")) {
        return "bytes_capacity";
    }
    if (bkr_str_eq(_v1656, "bytes_get")) {
        return "bytes_get";
    }
    if (bkr_str_eq(_v1656, "bytes_set")) {
        return "bytes_set";
    }
    if (bkr_str_eq(_v1656, "bytes_push")) {
        return "bytes_push";
    }
    if (bkr_str_eq(_v1656, "bytes_from_str")) {
        return "bytes_from_str";
    }
    if (bkr_str_eq(_v1656, "bytes_to_str")) {
        return "bytes_to_str";
    }
    if (bkr_str_eq(_v1656, "slice_new")) {
        return "slice_new";
    }
    if (bkr_str_eq(_v1656, "slice_len")) {
        return "slice_len";
    }
    if (bkr_str_eq(_v1656, "slice_get")) {
        return "slice_get";
    }
    if (bkr_str_eq(_v1656, "slice_sub")) {
        return "slice_sub";
    }
    if (bkr_str_eq(_v1656, "slice_to_vec")) {
        return "slice_to_vec";
    }
    if (bkr_str_eq(_v1656, "slice_contains")) {
        return "slice_contains";
    }
    if (bkr_str_eq(_v1656, "vec_as_slice")) {
        return "vec_as_slice";
    }
    if (bkr_str_eq(_v1656, "vec_slice")) {
        return "vec_slice";
    }
    if (bkr_str_eq(_v1656, "bytes_as_slice")) {
        return "bytes_as_slice";
    }
    if (bkr_str_eq(_v1656, "bytes_slice")) {
        return "bytes_slice";
    }
    if (bkr_str_eq(_v1656, "path_exists")) {
        return "path_exists";
    }
    if (bkr_str_eq(_v1656, "path_is_file")) {
        return "path_is_file";
    }
    if (bkr_str_eq(_v1656, "path_is_dir")) {
        return "path_is_dir";
    }
    if (bkr_str_eq(_v1656, "file_read")) {
        return "file_read";
    }
    if (bkr_str_eq(_v1656, "file_write")) {
        return "file_write";
    }
    if (bkr_str_eq(_v1656, "file_size")) {
        return "file_size";
    }
    if (bkr_str_eq(_v1656, "file_remove")) {
        return "file_remove";
    }
    if (bkr_str_eq(_v1656, "file_read_bytes")) {
        return "file_read_bytes";
    }
    if (bkr_str_eq(_v1656, "file_write_bytes")) {
        return "file_write_bytes";
    }
    if (bkr_str_eq(_v1656, "dir_create")) {
        return "dir_create";
    }
    if (bkr_str_eq(_v1656, "dir_remove")) {
        return "dir_remove";
    }
    if (bkr_str_eq(_v1656, "process_run")) {
        return "process_run";
    }
    if (bkr_str_eq(_v1656, "process_run_status")) {
        return "process_run_status";
    }
    if (bkr_str_eq(_v1656, "process_exit")) {
        return "process_exit";
    }
    if (bkr_str_eq(_v1656, "process_pid")) {
        return "process_pid";
    }
    if (bkr_str_eq(_v1656, "process_is_sandboxed")) {
        return "process_is_sandboxed";
    }
    return "";
}

bkr_str _v1657(bkr_i64 _v425, bkr_i64 _v1036) {
    bkr_str _v1656 = _v1641(_v425, _v1036);
    bkr_str _v1658 = _v1655(_v1656);
    if ((!bkr_str_eq(_v1658, ""))) {
        return _v1658;
    }
    if (starts_with(_v1656, "bkr_")) {
        return _v1656;
    }
    return bkr_str_concat("_v", int_to_string(_v1036));
}

bkr_str _v1660(bkr_i64 _v1254, bkr_i64 _v1036) {
    return _v1653(_v1564(_v1254), _v1036);
}

bkr_str _v1653(_v1547 _v1254, bkr_i64 _v1036) {
    return _v1657(_v1577(_v1254), _v1036);
}

bkr_i64 _v1661(bkr_i64 _v516) {
    return _v1662(_v517(_v516));
}

bkr_i64 _v1662(_v346 _v521) {
    return _v530(_v521);
}

bkr_i64 _v1663(bkr_i64 _v516) {
    return _v1664(_v517(_v516));
}

bkr_i64 _v1664(_v346 _v521) {
    return _v533(_v521);
}

bkr_i64 _v1665(bkr_i64 _v516) {
    return _v1666(_v517(_v516));
}

bkr_i64 _v1666(_v346 _v521) {
    return _v534(_v521);
}

bkr_i64 _v1667(bkr_str _v1656) {
    if (bkr_str_eq(_v1656, "len")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "strlen")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_new")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_push")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "vec_get")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_set")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "vec_len")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_pop")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_clear")) {
        return _v307;
    }
    if (bkr_str_eq(_v1656, "hashmap_new")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "hashmap_insert")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "hashmap_get")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "hashmap_contains")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "hashmap_remove")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "hashmap_keys")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "hashmap_len")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "hashmap_clear")) {
        return _v302;
    }
    if (bkr_str_eq(_v1656, "char_code")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "char_code_at")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "parse_int")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "char_at")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "substring")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "contains")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "starts_with")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "ends_with")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "trim")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "int_to_string")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "from_char_code")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "join_lines")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "read_file")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "write_file")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "file_exists")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "file_set_executable")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "result_ok")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "result_err")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "result_is_ok")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "result_is_err")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "result_unwrap")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "result_unwrap_err")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "result_tag")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "result_value")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "hashmap_get_opt")) {
        return _v312;
    }
    if (bkr_str_eq(_v1656, "vec_get_opt")) {
        return _v312;
    }
    if (bkr_str_eq(_v1656, "vec_pop_opt")) {
        return _v312;
    }
    if (bkr_str_eq(_v1656, "vec_contains")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "vec_is_empty")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "vec_clone")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_reverse")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "hashmap_is_empty")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "hashmap_values")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_map")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_filter")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_fold")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_find")) {
        return _v312;
    }
    if (bkr_str_eq(_v1656, "read_file_result")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "write_file_result")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "parse_int_result")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "bkr_tuple2")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "bkr_tuple3")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "bkr_tuple_get")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "args_count")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "arg_at")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "str_index_of")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "str_replace")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "str_split")) {
        return _v310;
    }
    if (bkr_str_eq(_v1656, "str_to_upper")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "str_to_lower")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "str_repeat")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "path_join")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "path_dir")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "path_base")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "path_ext")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "path_is_abs")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "env_var")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "env_get")) {
        return _v312;
    }
    if (bkr_str_eq(_v1656, "env_set")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "env_has")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "time_now_ms")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "time_now_unix")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "runtime_version_major")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "runtime_version_minor")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "runtime_version_patch")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "runtime_version_str")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "bytes_new")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "bytes_len")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "bytes_capacity")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "bytes_get")) {
        return _v302;
    }
    if (bkr_str_eq(_v1656, "bytes_set")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "bytes_push")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "bytes_from_str")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "bytes_to_str")) {
        return _v306;
    }
    if (bkr_str_eq(_v1656, "slice_new")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "slice_len")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "slice_get")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "slice_sub")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "slice_to_vec")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "slice_contains")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "vec_as_slice")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "vec_slice")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "bytes_as_slice")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "bytes_slice")) {
        return _v303;
    }
    if (bkr_str_eq(_v1656, "path_exists")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "path_is_file")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "path_is_dir")) {
        return _v305;
    }
    if (bkr_str_eq(_v1656, "file_read")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "file_write")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "file_size")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "file_remove")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "file_read_bytes")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "file_write_bytes")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "dir_create")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "dir_remove")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "process_run")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "process_run_status")) {
        return _v313;
    }
    if (bkr_str_eq(_v1656, "process_exit")) {
        return _v316;
    }
    if (bkr_str_eq(_v1656, "process_pid")) {
        return _v302;
    }
    if (bkr_str_eq(_v1656, "process_is_sandboxed")) {
        return _v305;
    }
    return _v316;
}

bkr_i64 _v1668(bkr_i64 _v1254, bkr_i64 _v368) {
    return _v1669(_v1564(_v1254), _v539(_v368));
}

bkr_i64 _v1670(bkr_i64 _v1254, bkr_i64 _v1671) {
    return _v1672(_v1564(_v1254), _v1671);
}

bkr_i64 _v1672(_v1547 _v1254, bkr_i64 _v1671) {
    if (_v524(_v1671)) {
        return _v316;
    }
    return _v1669(_v1254, _v538(_v1671));
}

_v346 _v1673(_v1547 _v1254, bkr_i64 _v1519, bkr_i64 _v1674) {
    bkr_i64 _v1567 = _v1568(_v1254);
    if (_v524(_v1567)) {
        return _v517(0);
    }
    _v341 _v1546 = _v507(_v1567);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v254) && (_v887(_v563) == _v1519))) {
            _v434 _v1162 = _v890(_v563);
            bkr_i64 _v1645 = 0;
            while ((_v1645 < _v907(_v1162))) {
                _v341 _v1447 = _v913(_v1162, _v1645);
                if ((_v892(_v1447) == _v1674)) {
                    return _v517(_v895(_v1447));
                }
                _v1645 = (_v1645 + 1);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v517(0);
}

bkr_i64 _v1675(_v1547 _v1254, bkr_i64 _v1519, bkr_i64 _v1647) {
    bkr_i64 _v1567 = _v1568(_v1254);
    if (_v524(_v1567)) {
        return (-1);
    }
    _v341 _v1546 = _v507(_v1567);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v254) && (_v887(_v563) == _v1519))) {
            _v434 _v1162 = _v890(_v563);
            if (((_v1647 >= 0) && (_v1647 < _v907(_v1162)))) {
                _v341 _v1447 = _v913(_v1162, _v1647);
                return _v892(_v1447);
            }
            return (-1);
        }
        _v1172 = (_v1172 + 1);
    }
    return (-1);
}

bkr_bool _v1676(_v1547 _v1254, bkr_i64 _v1519) {
    bkr_i64 _v1567 = _v1568(_v1254);
    if (_v524(_v1567)) {
        return BKR_FALSE;
    }
    _v341 _v1546 = _v507(_v1567);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v254) && (_v887(_v563) == _v1519))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v1677(_v1547 _v1254, bkr_i64 _v1519) {
    bkr_i64 _v1678 = _v1578(_v1254, "0");
    _v346 _v1679 = _v1673(_v1254, _v1519, _v1678);
    return _v525(_v1679);
}

bkr_str _v1680(_v1547 _v1254, bkr_i64 _v1519, bkr_str _v1681) {
    bkr_i64 _v1682 = _v1578(_v1254, _v1681);
    _v346 _v1683 = _v1673(_v1254, _v1519, _v1682);
    if (_v525(_v1683)) {
        return _v1652(_v1254, _v1683);
    }
    return "bkr_i64";
}

_v346 _v1684(_v1547 _v1254, bkr_i64 _v1545) {
    bkr_i64 _v1567 = _v1568(_v1254);
    if (_v524(_v1567)) {
        return _v517(0);
    }
    _v341 _v1546 = _v507(_v1567);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v224) && (_v869(_v563) == _v1545))) {
            bkr_i64 _v1685 = _v875(_v563);
            if (_v526(_v1685)) {
                return _v517(_v1685);
            }
            return _v517(0);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v517(0);
}

bkr_i64 _v1669(_v1547 _v1254, _v426 _v542) {
    bkr_i64 _v1686 = _v545(_v542);
    if ((_v1686 == _v246)) {
        return _v303;
    }
    if ((_v1686 == _v251)) {
        return _v304;
    }
    if ((_v1686 == _v247)) {
        return _v305;
    }
    if ((_v1686 == _v248)) {
        return _v306;
    }
    if ((_v1686 == _v227)) {
        _v429 _v583 = _v579(_v541(_v542));
        bkr_i64 _v399 = _v590(_v583);
        if ((_v399 > 0)) {
            _v427 _v1687 = _v1111(_v583, (_v399 - 1));
            if ((_v556(_v1687) == _v232)) {
                return _v1669(_v1254, _v538(_v861(_v1687)));
            }
        }
        return _v307;
    }
    if ((_v1686 == _v252)) {
        return _v308;
    }
    if ((_v1686 == _v257)) {
        return _v309;
    }
    if ((_v1686 == _v245)) {
        bkr_i64 _v425 = _v1577(_v1254);
        bkr_i64 _v355 = _v663(_v542);
        bkr_str _v1656 = _v1641(_v425, _v355);
        if (bkr_str_eq(_v1656, "None")) {
            return _v312;
        }
        return _v1635(_v1254, _v355);
    }
    if ((_v1686 == _v239)) {
        return _v308;
    }
    if ((_v1686 == _v253)) {
        _v426 _v1038 = _v538(_v712(_v542));
        if ((_v545(_v1038) == _v245)) {
            return _v1631(_v1254, _v663(_v1038));
        }
        if ((_v545(_v1038) == _v256)) {
            _v426 _v1688 = _v538(_v720(_v1038));
            if ((_v545(_v1688) == _v245)) {
                bkr_i64 _v1519 = _v1612(_v1254, _v663(_v1688));
                if ((_v1519 >= 0)) {
                    _v346 _v1156 = _v1673(_v1254, _v1519, _v723(_v1038));
                    if ((_v525(_v1156) && (_v530(_v1156) == _v308))) {
                        return _v533(_v1156);
                    }
                }
            }
        }
        return _v316;
    }
    if ((_v1686 == _v256)) {
        _v426 _v1038 = _v538(_v720(_v542));
        if ((_v545(_v1038) == _v245)) {
            if (_v1639(_v1254, _v663(_v1038))) {
                return _v303;
            }
            bkr_i64 _v1519 = _v1612(_v1254, _v663(_v1038));
            if ((_v1519 >= 0)) {
                _v346 _v1156 = _v1673(_v1254, _v1519, _v723(_v542));
                if (_v525(_v1156)) {
                    return _v530(_v1156);
                }
            }
        }
        return _v316;
    }
    if ((_v1686 == _v242)) {
        bkr_i64 _v349 = _v672(_v542);
        _v426 _v1051 = _v538(_v675(_v542));
        _v426 _v1052 = _v538(_v678(_v542));
        if (((_v349 == _v176) && (_v545(_v1052) == _v256))) {
            _v426 _v1689 = _v538(_v720(_v1052));
            if ((_v545(_v1689) == _v245)) {
                bkr_i64 _v425 = _v1577(_v1254);
                bkr_str _v1642 = _v1641(_v425, _v663(_v1689));
                bkr_str _v1644 = _v1641(_v425, _v723(_v1052));
                bkr_i64 _v1690 = _v1643(_v1254, _v1642, _v1644);
                if ((_v1690 >= 0)) {
                    return _v303;
                }
            }
        }
        bkr_i64 _v1691 = _v1669(_v1254, _v1051);
        bkr_i64 _v1692 = _v1669(_v1254, _v1052);
        if (((_v349 == _v161) && ((_v1691 == _v306) || (_v1692 == _v306)))) {
            return _v306;
        }
        if (((((((((_v349 == _v166) || (_v349 == _v167)) || (_v349 == _v168)) || (_v349 == _v169)) || (_v349 == _v170)) || (_v349 == _v171)) || (_v349 == _v172)) || (_v349 == _v173))) {
            return _v305;
        }
        return _v1691;
    }
    if ((_v1686 == _v250)) {
        bkr_i64 _v1693 = _v1669(_v1254, _v538(_v737(_v542)));
        if ((_v1693 != _v314)) {
            return _v1693;
        }
        return _v1669(_v1254, _v538(_v740(_v542)));
    }
    if ((_v1686 == _v240)) {
        _v426 _v1694 = _v538(_v778(_v542));
        bkr_i64 _v1382 = _v1669(_v1254, _v1694);
        if (((_v1382 == _v313) || (_v1382 == _v312))) {
            if ((_v545(_v1694) == _v244)) {
                _v346 _v1695 = _v1684(_v1254, _v689(_v1694));
                if (_v525(_v1695)) {
                    bkr_i64 _v1696 = _v535(_v1695);
                    if (((_v1696 > 0) && (_v1696 != _v316))) {
                        return _v1696;
                    }
                }
            }
            return _v303;
        }
        return _v1382;
    }
    if ((_v1686 == _v241)) {
        _v346 _v1450 = _v517(_v783(_v542));
        return _v530(_v1450);
    }
    if ((_v1686 == _v243)) {
        bkr_i64 _v349 = _v682(_v542);
        if ((_v349 == _v174)) {
            return _v305;
        }
        return _v1669(_v1254, _v538(_v685(_v542)));
    }
    if ((_v1686 == _v258)) {
        _v434 _v976 = _v749(_v542);
        if ((_v907(_v976) > 0)) {
            _v341 _v1127 = _v913(_v976, 0);
            if ((_v510(_v1127) == _v227)) {
                _v429 _v583 = _v581(_v1127);
                if ((_v590(_v583) <= 0)) {
                    return _v316;
                }
                _v427 _v1687 = _v1111(_v583, (_v590(_v583) - 1));
                if ((_v556(_v1687) == _v232)) {
                    return _v1669(_v1254, _v538(_v861(_v1687)));
                }
                return _v316;
            }
            return _v1669(_v1254, _v540(_v1127));
        }
        return _v316;
    }
    if ((_v1686 == _v261)) {
        _v426 _v1022 = _v695(_v542);
        bkr_i64 _v1519 = (-1);
        if ((_v545(_v1022) == _v245)) {
            _v1519 = _v1612(_v1254, _v663(_v1022));
        }
        if ((_v1519 >= 0)) {
            bkr_i64 _v425 = _v1577(_v1254);
            bkr_str _v1697 = _v1641(_v425, _v1519);
            bkr_str _v1698 = _v1641(_v425, _v697(_v542));
            bkr_str _v1439 = bkr_str_concat(bkr_str_concat(_v1697, "::"), _v1698);
            bkr_i64 _v1699 = _v1578(_v1254, _v1439);
            bkr_i64 _v1700 = _v1638(_v1254, _v1699);
            if ((_v1700 != _v316)) {
                return _v1700;
            }
            _v346 _v1695 = _v1684(_v1254, _v1699);
            if (_v525(_v1695)) {
                return _v530(_v1695);
            }
        }
        return _v316;
    }
    if ((_v1686 == _v244)) {
        bkr_i64 _v355 = _v689(_v542);
        if (_v1676(_v1254, _v355)) {
            return _v309;
        }
        bkr_i64 _v1701 = _v1635(_v1254, _v355);
        if ((_v1701 == _v315)) {
            return _v303;
        }
        bkr_i64 _v425 = _v1577(_v1254);
        bkr_str _v1656 = _v1641(_v425, _v355);
        if (bkr_str_eq(_v1656, "panic")) {
            return _v314;
        }
        if (bkr_str_eq(_v1656, "Some")) {
            return _v312;
        }
        if ((bkr_str_eq(_v1656, "Ok") || bkr_str_eq(_v1656, "Err"))) {
            return _v313;
        }
        if ((bkr_str_eq(_v1656, "vec_get") || bkr_str_eq(_v1656, "vec_pop"))) {
            _v434 _v1016 = _v692(_v542);
            if ((_v907(_v1016) > 0)) {
                _v426 _v1702 = _v538(_v910(_v1016, 0));
                if ((_v545(_v1702) == _v245)) {
                    bkr_i64 _v1703 = _v1631(_v1254, _v1025(_v1702));
                    if (((_v1703 != _v316) && (_v1703 != 0))) {
                        return _v1703;
                    }
                }
            }
        }
        bkr_i64 _v1704 = _v1667(_v1656);
        if ((_v1704 != _v316)) {
            return _v1704;
        }
        bkr_i64 _v1700 = _v1638(_v1254, _v355);
        if ((_v1700 != _v316)) {
            return _v1700;
        }
        _v346 _v1695 = _v1684(_v1254, _v355);
        if (_v525(_v1695)) {
            return _v530(_v1695);
        }
        return _v316;
    }
    return _v316;
}

bkr_str _v1705(bkr_i64 _v1254, bkr_i64 _v370) {
    return _v1706(_v1564(_v1254), _v551(_v370));
}

bkr_str _v1706(_v1547 _v1254, _v427 _v554) {
    bkr_str _v1363 = _v1653(_v1254, _v758(_v554));
    bkr_i64 _v516 = _v761(_v554);
    bkr_i64 _v366 = _v764(_v554);
    if ((_v526(_v516) && (_v1662(_v517(_v516)) == _v308))) {
        bkr_i64 _v954 = _v1664(_v517(_v516));
        bkr_i64 _v1707 = _v1666(_v517(_v516));
        bkr_str _v1598 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1650(_v954), " "), _v1363), "["), int_to_string(_v1707)), "]");
        if (_v526(_v366)) {
            _v1598 = bkr_str_concat(bkr_str_concat(_v1598, " = "), _v1708(_v1254, _v538(_v366)));
        }
        return bkr_str_concat(_v1598, "; ");
    }
    if ((_v524(_v516) && _v526(_v366))) {
        _v426 _v1709 = _v538(_v366);
        bkr_i64 _v1710 = _v545(_v1709);
        if ((_v1710 == _v252)) {
            _v434 _v995 = _v702(_v1709);
            bkr_i64 _v1707 = _v907(_v995);
            if ((_v1707 > 0)) {
                bkr_i64 _v954 = _v1669(_v1254, _v538(_v910(_v995, 0)));
                bkr_str _v1598 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1650(_v954), " "), _v1363), "["), int_to_string(_v1707)), "] = "), _v1708(_v1254, _v1709));
                return bkr_str_concat(_v1598, "; ");
            }
        } else {
            if ((_v1710 == _v239)) {
                bkr_i64 _v1707 = _v707(_v1709);
                bkr_i64 _v954 = _v1669(_v1254, _v705(_v1709));
                bkr_str _v1598 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1650(_v954), " "), _v1363), "["), int_to_string(_v1707)), "] = "), _v1708(_v1254, _v1709));
                return bkr_str_concat(_v1598, "; ");
            }
        }
    }
    bkr_i64 _v319 = _v303;
    bkr_i64 _v1519 = (-1);
    if (_v526(_v516)) {
        _v319 = _v1662(_v517(_v516));
        if ((_v319 == _v309)) {
            _v1519 = _v532(_v517(_v516));
        }
    } else {
        if (_v526(_v366)) {
            bkr_i64 _v1711 = _v1672(_v1254, _v366);
            if (((_v1711 != _v316) && (_v1711 != _v307))) {
                _v319 = _v1711;
            }
            _v426 _v1709 = _v538(_v366);
            if ((_v545(_v1709) == _v257)) {
                _v319 = _v309;
                _v1519 = _v725(_v1709);
            } else {
                if ((_v545(_v1709) == _v244)) {
                    bkr_i64 _v1712 = _v689(_v1709);
                    if (_v1676(_v1254, _v1712)) {
                        _v319 = _v309;
                        _v1519 = _v1712;
                    } else {
                        _v346 _v1695 = _v1684(_v1254, _v1712);
                        if ((_v525(_v1695) && (_v530(_v1695) == _v309))) {
                            _v319 = _v309;
                            _v1519 = _v532(_v1695);
                        }
                    }
                } else {
                    if ((_v545(_v1709) == _v245)) {
                        bkr_i64 _v1713 = _v1612(_v1254, _v1025(_v1709));
                        if ((_v1713 >= 0)) {
                            _v319 = _v309;
                            _v1519 = _v1713;
                        }
                    } else {
                        if ((_v545(_v1709) == _v227)) {
                            _v429 _v583 = _v579(_v541(_v1709));
                            bkr_i64 _v399 = _v590(_v583);
                            if ((_v399 > 0)) {
                                _v427 _v1687 = _v1111(_v583, (_v399 - 1));
                                if ((_v556(_v1687) == _v232)) {
                                    _v426 _v1714 = _v538(_v861(_v1687));
                                    bkr_i64 _v1715 = _v545(_v1714);
                                    if ((_v1715 == _v257)) {
                                        _v319 = _v309;
                                        _v1519 = _v725(_v1714);
                                    } else {
                                        if ((_v1715 == _v245)) {
                                            bkr_i64 _v1713 = _v1612(_v1254, _v663(_v1714));
                                            if ((_v1713 >= 0)) {
                                                _v319 = _v309;
                                                _v1519 = _v1713;
                                            }
                                        } else {
                                            if (((_v1715 == _v244) && _v1676(_v1254, _v689(_v1714)))) {
                                                _v319 = _v309;
                                                _v1519 = _v689(_v1714);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    bkr_str _v1716 = _v1650(_v319);
    if (_v526(_v516)) {
        _v1716 = _v1652(_v1254, _v517(_v516));
    } else {
        if (((_v319 == _v309) && (_v1519 >= 0))) {
            if (_v1639(_v1254, _v1519)) {
                _v1716 = "bkr_i64";
            } else {
                _v1716 = _v1653(_v1254, _v1519);
            }
        }
    }
    bkr_str _v1598 = bkr_str_concat(bkr_str_concat(_v1716, " "), _v1363);
    if (_v526(_v366)) {
        _v1598 = bkr_str_concat(bkr_str_concat(_v1598, " = "), _v1717(_v1254, _v516, _v538(_v366)));
    }
    return bkr_str_concat(_v1598, "; ");
}

bkr_str _v1718(bkr_i64 _v1254, bkr_str _v1719, bkr_i64 _v379) {
    return _v1720(_v1564(_v1254), _v1719, _v477(_v379));
}

bkr_str _v1720(_v1547 _v1254, bkr_str _v1719, _v341 _v1127) {
    if ((_v510(_v1127) != _v227)) {
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1719, " = "), _v1708(_v1254, _v540(_v1127))), "; ");
    }
    _v429 _v583 = _v581(_v1127);
    bkr_str _v1196 = "{ ";
    bkr_i64 _v1172 = 0;
    bkr_i64 _v399 = _v590(_v583);
    while ((_v1172 < _v399)) {
        _v427 _v554 = _v1111(_v583, _v1172);
        bkr_i64 _v1721 = _v556(_v554);
        bkr_bool _v1722 = (_v1172 == (_v399 - 1));
        if ((_v1722 && (_v1721 == _v232))) {
            if ((!bkr_str_eq(_v1719, ""))) {
                _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1719), " = "), _v1708(_v1254, _v538(_v861(_v554)))), "; ");
            } else {
                _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1708(_v1254, _v538(_v861(_v554)))), "; ");
            }
        } else {
            if ((_v1721 == _v228)) {
                _v1196 = bkr_str_concat(_v1196, _v1706(_v1254, _v554));
            } else {
                if ((_v1721 == _v233)) {
                    _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1708(_v1254, _v538(_v855(_v554)))), " = "), _v1708(_v1254, _v538(_v858(_v554)))), "; ");
                } else {
                    if ((_v1721 == _v232)) {
                        _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1708(_v1254, _v538(_v861(_v554)))), "; ");
                    } else {
                        if ((_v1721 == _v229)) {
                            bkr_i64 _v1723 = _v769(_v554);
                            if (_v526(_v1723)) {
                                _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, "return "), _v1708(_v1254, _v538(_v1723))), "; ");
                            } else {
                                _v1196 = bkr_str_concat(_v1196, "return; ");
                            }
                        }
                    }
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "} ");
}

bkr_str _v1724(bkr_i64 _v1254, bkr_str _v1725, bkr_i64 _v463) {
    return _v1726(_v1564(_v1254), _v1725, _v593(_v463));
}

bkr_str _v1726(_v1547 _v1254, bkr_str _v1725, _v433 _v473) {
    bkr_i64 _v319 = _v597(_v473);
    bkr_i64 _v387 = _v598(_v473);
    if ((_v319 == _v283)) {
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1725), " == "), int_to_string(_v387)), ")");
    }
    if ((_v319 == _v284)) {
        if ((_v387 != 0)) {
            return bkr_str_concat(bkr_str_concat("(", _v1725), " == BKR_TRUE)");
        }
        return bkr_str_concat(bkr_str_concat("(", _v1725), " == BKR_FALSE)");
    }
    if (((_v319 == _v285) || (_v319 == _v286))) {
        return "BKR_TRUE";
    }
    if ((_v319 == _v287)) {
        bkr_str _v1727 = bkr_str_concat(bkr_str_concat("((", _v1725), " & 1) != 0)");
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            _v433 _v1408 = _v592(_v345);
            bkr_str _v1728 = _v1726(_v1254, bkr_str_concat(bkr_str_concat("(", _v1725), " >> 1)"), _v1408);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1727), " && "), _v1728), ")");
        }
        return _v1727;
    }
    if ((_v319 == _v288)) {
        return bkr_str_concat(bkr_str_concat("(", _v1725), " == 0)");
    }
    if ((_v319 == _v290)) {
        bkr_str _v1727 = bkr_str_concat(bkr_str_concat("(bkr_result_is_ok(", _v1725), ") == BKR_TRUE)");
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            _v433 _v1408 = _v592(_v345);
            bkr_str _v1728 = _v1726(_v1254, bkr_str_concat(bkr_str_concat("bkr_result_unwrap(", _v1725), ")"), _v1408);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1727), " && "), _v1728), ")");
        }
        return _v1727;
    }
    if ((_v319 == _v291)) {
        bkr_str _v1727 = bkr_str_concat(bkr_str_concat("(bkr_result_is_err(", _v1725), ") == BKR_TRUE)");
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            _v433 _v1408 = _v592(_v345);
            bkr_str _v1728 = _v1726(_v1254, bkr_str_concat(bkr_str_concat("bkr_result_unwrap_err(", _v1725), ")"), _v1408);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1727), " && "), _v1728), ")");
        }
        return _v1727;
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            bkr_i64 _v1390 = ((bkr_i64)(_v345));
            bkr_str _v375 = "";
            bkr_i64 _v1172 = 0;
            while ((_v1172 < vec_len(_v1390))) {
                _v433 _v1408 = _v592(vec_get(_v1390, _v1172));
                bkr_str _v1729 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_tuple_get(", _v1725), ", "), int_to_string(_v1172)), ")");
                bkr_str _v1728 = _v1726(_v1254, _v1729, _v1408);
                if ((!bkr_str_eq(_v1728, "BKR_TRUE"))) {
                    if (bkr_str_eq(_v375, "")) {
                        _v375 = bkr_str_concat(bkr_str_concat("(", _v1728), ")");
                    } else {
                        _v375 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v375), " && "), _v1728), ")");
                    }
                }
                _v1172 = (_v1172 + 1);
            }
            if ((!bkr_str_eq(_v375, ""))) {
                return _v375;
            }
        }
        return "BKR_TRUE";
    }
    if ((_v319 == _v293)) {
        return "BKR_TRUE";
    }
    if ((_v319 == _v289)) {
        bkr_i64 _v425 = _v1577(_v1254);
        bkr_str _v1642 = _v1641(_v425, _v387);
        bkr_str _v1644 = _v1641(_v425, _v599(_v473));
        bkr_i64 _v1690 = _v1643(_v1254, _v1642, _v1644);
        if ((_v1690 >= 0)) {
            if (_v1649(_v1254, _v1642)) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(bkr_enum_tag(", _v1725), ") == "), int_to_string(_v1690)), ")");
            }
            if ((_v600(_v473) >= 0)) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("((", _v1725), " & 255) == "), int_to_string(_v1690)), ")");
            }
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1725), " == "), int_to_string(_v1690)), ")");
        }
    }
    return "BKR_FALSE";
}

bkr_str _v1730(bkr_i64 _v1254, bkr_str _v1725, bkr_i64 _v463, bkr_i64 _v1731) {
    return _v1732(_v1564(_v1254), _v1725, _v593(_v463), _v1731);
}

bkr_str _v1732(_v1547 _v1254, bkr_str _v1725, _v433 _v473, bkr_i64 _v1731) {
    bkr_i64 _v319 = _v597(_v473);
    bkr_i64 _v387 = _v598(_v473);
    if ((_v319 == _v285)) {
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1650(_v1731), " "), _v1653(_v1254, _v387)), " = "), _v1725), "; ");
    }
    if ((_v319 == _v287)) {
        bkr_str _v1733 = "";
        if ((_v387 >= 0)) {
            _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, "bkr_i64 "), _v1653(_v1254, _v387)), " = ("), _v1725), " >> 1); ");
        }
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            _v433 _v1408 = _v592(_v345);
            bkr_str _v1734 = bkr_str_concat(bkr_str_concat("(", _v1725), " >> 1)");
            _v1733 = bkr_str_concat(_v1733, _v1732(_v1254, _v1734, _v1408, _v303));
        }
        return _v1733;
    }
    if ((_v319 == _v290)) {
        bkr_str _v1733 = "";
        if ((_v387 >= 0)) {
            _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, "bkr_i64 "), _v1653(_v1254, _v387)), " = bkr_result_unwrap("), _v1725), "); ");
        }
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            _v433 _v1408 = _v592(_v345);
            bkr_str _v1734 = bkr_str_concat(bkr_str_concat("bkr_result_unwrap(", _v1725), ")");
            _v1733 = bkr_str_concat(_v1733, _v1732(_v1254, _v1734, _v1408, _v303));
        }
        return _v1733;
    }
    if ((_v319 == _v291)) {
        bkr_str _v1733 = "";
        if ((_v387 >= 0)) {
            _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, "bkr_i64 "), _v1653(_v1254, _v387)), " = bkr_result_unwrap_err("), _v1725), "); ");
        }
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            _v433 _v1408 = _v592(_v345);
            bkr_str _v1734 = bkr_str_concat(bkr_str_concat("bkr_result_unwrap_err(", _v1725), ")");
            _v1733 = bkr_str_concat(_v1733, _v1732(_v1254, _v1734, _v1408, _v303));
        }
        return _v1733;
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            bkr_i64 _v1390 = ((bkr_i64)(_v345));
            bkr_str _v1733 = "";
            bkr_i64 _v1172 = 0;
            while ((_v1172 < vec_len(_v1390))) {
                _v433 _v1408 = _v592(vec_get(_v1390, _v1172));
                bkr_str _v1729 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_tuple_get(", _v1725), ", "), int_to_string(_v1172)), ")");
                _v1733 = bkr_str_concat(_v1733, _v1732(_v1254, _v1729, _v1408, _v303));
                _v1172 = (_v1172 + 1);
            }
            return _v1733;
        }
        bkr_i64 _v1392 = _v600(_v473);
        bkr_i64 _v432 = _v601(_v473);
        bkr_i64 _v1393 = _v598(_v473);
        bkr_str _v1733 = "";
        if ((_v1392 >= 0)) {
            _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, "bkr_i64 "), _v1653(_v1254, _v1392)), " = bkr_tuple_get("), _v1725), ", 0); ");
        }
        if ((_v432 >= 0)) {
            _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, "bkr_i64 "), _v1653(_v1254, _v432)), " = bkr_tuple_get("), _v1725), ", 1); ");
        }
        if ((_v1393 >= 0)) {
            _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, "bkr_i64 "), _v1653(_v1254, _v1393)), " = bkr_tuple_get("), _v1725), ", 2); ");
        }
        return _v1733;
    }
    if ((_v319 == _v293)) {
        bkr_i64 _v1519 = _v598(_v473);
        bkr_bool _v1735 = _v1677(_v1254, _v1519);
        bkr_i64 _v1400 = _v600(_v473);
        bkr_i64 _v1401 = _v601(_v473);
        bkr_i64 _v1402 = _v599(_v473);
        bkr_str _v1733 = "";
        if (_v1735) {
            if ((_v1400 >= 0)) {
                bkr_str _v1736 = _v1653(_v1254, _v1400);
                bkr_str _v1737 = _v1653(_v1254, _v1578(_v1254, "0"));
                bkr_str _v1716 = _v1680(_v1254, _v1519, "0");
                _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, _v1716), " "), _v1736), " = "), _v1725), "."), _v1737), "; ");
            }
            if ((_v1401 >= 0)) {
                bkr_str _v1736 = _v1653(_v1254, _v1401);
                bkr_str _v1738 = _v1653(_v1254, _v1578(_v1254, "1"));
                bkr_str _v1716 = _v1680(_v1254, _v1519, "1");
                _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, _v1716), " "), _v1736), " = "), _v1725), "."), _v1738), "; ");
            }
            if ((_v1402 >= 0)) {
                bkr_str _v1736 = _v1653(_v1254, _v1402);
                bkr_str _v1739 = _v1653(_v1254, _v1578(_v1254, "2"));
                bkr_str _v1716 = _v1680(_v1254, _v1519, "2");
                _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, _v1716), " "), _v1736), " = "), _v1725), "."), _v1739), "; ");
            }
            return _v1733;
        }
        if ((_v1400 >= 0)) {
            bkr_i64 _v1740 = _v1675(_v1254, _v1519, 0);
            bkr_str _v1741 = _v1653(_v1254, _v1400);
            if ((_v1740 >= 0)) {
                _v1741 = _v1653(_v1254, _v1740);
            }
            bkr_str _v1742 = _v1653(_v1254, _v1400);
            _v346 _v1683 = _v1673(_v1254, _v1519, _v1740);
            bkr_str _v1716 = "bkr_i64";
            if (_v525(_v1683)) {
                _v1716 = _v1652(_v1254, _v1683);
            }
            _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, _v1716), " "), _v1742), " = "), _v1725), "."), _v1741), "; ");
        }
        if ((_v1401 >= 0)) {
            bkr_i64 _v1743 = _v1675(_v1254, _v1519, 1);
            bkr_str _v1744 = _v1653(_v1254, _v1401);
            if ((_v1743 >= 0)) {
                _v1744 = _v1653(_v1254, _v1743);
            }
            bkr_str _v1745 = _v1653(_v1254, _v1401);
            _v346 _v1683 = _v1673(_v1254, _v1519, _v1743);
            bkr_str _v1716 = "bkr_i64";
            if (_v525(_v1683)) {
                _v1716 = _v1652(_v1254, _v1683);
            }
            _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, _v1716), " "), _v1745), " = "), _v1725), "."), _v1744), "; ");
        }
        if ((_v1402 >= 0)) {
            bkr_i64 _v1746 = _v1675(_v1254, _v1519, 2);
            bkr_str _v1747 = _v1653(_v1254, _v1402);
            if ((_v1746 >= 0)) {
                _v1747 = _v1653(_v1254, _v1746);
            }
            bkr_str _v1748 = _v1653(_v1254, _v1402);
            _v346 _v1683 = _v1673(_v1254, _v1519, _v1746);
            bkr_str _v1716 = "bkr_i64";
            if (_v525(_v1683)) {
                _v1716 = _v1652(_v1254, _v1683);
            }
            _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, _v1716), " "), _v1748), " = "), _v1725), "."), _v1747), "; ");
        }
        return _v1733;
    }
    if ((_v319 == _v289)) {
        bkr_i64 _v1405 = _v600(_v473);
        if ((_v1405 >= 0)) {
            bkr_i64 _v425 = _v1577(_v1254);
            bkr_str _v1642 = _v1641(_v425, _v387);
            bkr_str _v1644 = _v1641(_v425, _v599(_v473));
            bkr_i64 _v1749 = _v1646(_v1254, _v1642, _v1644, 0);
            if (_v1649(_v1254, _v1642)) {
                bkr_i64 _v1406 = _v601(_v473);
                bkr_str _v1733 = "";
                if ((_v1749 == _v306)) {
                    _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str ", _v1653(_v1254, _v1405)), " = (bkr_str)(intptr_t)bkr_enum_field("), _v1725), ", 0); ");
                } else {
                    _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_i64 ", _v1653(_v1254, _v1405)), " = bkr_enum_field("), _v1725), ", 0); ");
                }
                if ((_v1406 >= 0)) {
                    bkr_i64 _v1750 = _v1646(_v1254, _v1642, _v1644, 1);
                    if ((_v1750 == _v306)) {
                        _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, "bkr_str "), _v1653(_v1254, _v1406)), " = (bkr_str)(intptr_t)bkr_enum_field("), _v1725), ", 1); ");
                    } else {
                        _v1733 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1733, "bkr_i64 "), _v1653(_v1254, _v1406)), " = bkr_enum_field("), _v1725), ", 1); ");
                    }
                }
                return _v1733;
            }
            bkr_i64 _v1406 = _v601(_v473);
            if ((_v1406 >= 0)) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_i64 ", _v1653(_v1254, _v1405)), " = ("), _v1725), " >> 20); "), "bkr_i64 "), _v1653(_v1254, _v1406)), " = (("), _v1725), " >> 8) & 4095); ");
            }
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_i64 ", _v1653(_v1254, _v1405)), " = ("), _v1725), " >> 8); ");
        }
    }
    return "";
}

bkr_str _v1751(bkr_i64 _v1254, bkr_i64 _v368) {
    return _v1752(_v1564(_v1254), _v539(_v368));
}

bkr_str _v1752(_v1547 _v1254, _v426 _v542) {
    _v426 _v975 = _v538(_v743(_v542));
    bkr_i64 _v1731 = _v1669(_v1254, _v975);
    bkr_i64 _v1753 = _v1669(_v1254, _v542);
    if (((_v1753 == _v316) || (_v1753 == _v307))) {
        _v1753 = _v303;
    }
    bkr_str _v1754 = _v1650(_v1731);
    if (((_v1731 == _v309) && (_v545(_v975) == _v245))) {
        bkr_i64 _v1755 = _v1612(_v1254, _v663(_v975));
        if ((_v1755 >= 0)) {
            if (_v1639(_v1254, _v1755)) {
                _v1754 = "bkr_i64";
            } else {
                _v1754 = _v1653(_v1254, _v1755);
            }
        }
    }
    bkr_str _v1725 = _v1620(_v1254, "_match_val");
    bkr_str _v1719 = _v1620(_v1254, "_match_res");
    bkr_str _v1756 = _v1620(_v1254, "_matched");
    bkr_str _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("({ ", _v1754), " "), _v1725), " = "), _v1708(_v1254, _v975)), "; "), _v1650(_v1753)), " "), _v1719), " = 0; int "), _v1756), " = 0; ");
    _v436 _v621 = _v746(_v542);
    _v434 _v976 = _v749(_v542);
    _v435 _v977 = _v751(_v542);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        _v433 _v473 = _v925(_v621, _v1172);
        _v341 _v1127 = _v913(_v976, _v1172);
        bkr_i64 _v1413 = 0;
        if ((_v1172 < _v916(_v977))) {
            _v1413 = _v918(_v977, _v1172);
        }
        bkr_str _v1757 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("!", _v1756), " && ("), _v1726(_v1254, _v1725, _v473)), ")");
        _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, "if ("), _v1757), ") { "), _v1732(_v1254, _v1725, _v473, _v1731));
        if ((_v1413 != 0)) {
            _v426 _v1758 = _v538(_v1413);
            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, "if ("), _v1708(_v1254, _v1758)), ") { "), _v1720(_v1254, _v1719, _v1127)), _v1756), " = 1; } } ");
        } else {
            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1720(_v1254, _v1719, _v1127)), _v1756), " = 1; } ");
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(bkr_str_concat(_v1196, _v1719), "; })");
}

bkr_bool _v1759(bkr_i64 _v1254, bkr_i64 _v368) {
    return _v1760(_v1564(_v1254), _v539(_v368));
}

bkr_bool _v1760(_v1547 _v1254, _v426 _v542) {
    if ((_v545(_v542) != _v244)) {
        return BKR_FALSE;
    }
    bkr_i64 _v355 = _v689(_v542);
    bkr_i64 _v425 = _v1577(_v1254);
    bkr_str _v1656 = _v1641(_v425, _v355);
    return (((((bkr_str_eq(_v1656, "result_unwrap") || bkr_str_eq(_v1656, "result_unwrap_err")) || bkr_str_eq(_v1656, "result_value")) || bkr_str_eq(_v1656, "vec_get")) || bkr_str_eq(_v1656, "vec_pop")) || bkr_str_eq(_v1656, "hashmap_get"));
}

bkr_str _v1761(bkr_i64 _v1254, bkr_i64 _v368) {
    return _v1762(_v1564(_v1254), _v539(_v368));
}

bkr_str _v1762(_v1547 _v1254, _v426 _v542) {
    bkr_str _v1196 = _v1708(_v1254, _v542);
    bkr_i64 _v319 = _v1669(_v1254, _v542);
    if ((_v319 == _v306)) {
        return bkr_str_concat(bkr_str_concat("((bkr_i64)(intptr_t)", _v1196), ")");
    }
    return _v1196;
}

bkr_str _v1763(bkr_i64 _v1254, bkr_i64 _v516, bkr_i64 _v366) {
    return _v1717(_v1564(_v1254), _v516, _v539(_v366));
}

bkr_str _v1717(_v1547 _v1254, bkr_i64 _v516, _v426 _v1709) {
    if ((_v526(_v516) && (_v1662(_v517(_v516)) == _v311))) {
        bkr_i64 _v1378 = _v535(_v517(_v516));
        if (((_v1378 == _v306) && (_v545(_v1709) == _v244))) {
            bkr_i64 _v355 = _v689(_v1709);
            bkr_i64 _v425 = _v1577(_v1254);
            bkr_str _v1764 = _v1641(_v425, _v355);
            if (bkr_str_eq(_v1764, "hashmap_new")) {
                return "hashmap_new_str()";
            }
        }
    }
    bkr_str _v1196 = _v1708(_v1254, _v1709);
    if (((_v526(_v516) && (_v1662(_v517(_v516)) == _v306)) && _v1760(_v1254, _v1709))) {
        return bkr_str_concat(bkr_str_concat("(bkr_str)(intptr_t)(", _v1196), ")");
    }
    return _v1196;
}

bkr_str _v1765(bkr_i64 _v1254, bkr_i64 _v368) {
    return _v1708(_v1564(_v1254), _v539(_v368));
}

bkr_str _v1708(_v1547 _v1254, _v426 _v542) {
    bkr_i64 _v1686 = _v545(_v542);
    if ((_v1686 == _v246)) {
        return int_to_string(_v666(_v542));
    }
    if ((_v1686 == _v251)) {
        return ((bkr_str)(_v666(_v542)));
    }
    if ((_v1686 == _v247)) {
        if ((_v666(_v542) == 1)) {
            return "BKR_TRUE";
        }
        return "BKR_FALSE";
    }
    if ((_v1686 == _v248)) {
        bkr_str _v1656 = ((bkr_str)(_v666(_v542)));
        return _v1766(_v1656);
    }
    if ((_v1686 == _v227)) {
        bkr_str _v1767 = _v1620(_v1254, "_blk_res");
        bkr_i64 _v1768 = _v1669(_v1254, _v542);
        bkr_str _v1769 = _v1650(_v1768);
        if ((_v1768 == _v309)) {
            _v429 _v583 = _v579(_v541(_v542));
            bkr_i64 _v399 = _v590(_v583);
            if ((_v399 > 0)) {
                _v427 _v1687 = _v1111(_v583, (_v399 - 1));
                if ((_v556(_v1687) == _v232)) {
                    _v426 _v1714 = _v538(_v861(_v1687));
                    bkr_i64 _v1715 = _v545(_v1714);
                    bkr_i64 _v1713 = (-1);
                    if ((_v1715 == _v257)) {
                        _v1713 = _v725(_v1714);
                    } else {
                        if ((_v1715 == _v245)) {
                            _v1713 = _v1612(_v1254, _v663(_v1714));
                        } else {
                            if (((_v1715 == _v244) && _v1676(_v1254, _v689(_v1714)))) {
                                _v1713 = _v689(_v1714);
                            }
                        }
                    }
                    if ((_v1713 >= 0)) {
                        _v1769 = _v1653(_v1254, _v1713);
                    }
                }
            }
        }
        if ((_v1768 == _v307)) {
            return bkr_str_concat(bkr_str_concat("({ ", _v1720(_v1254, "", _v507(_v541(_v542)))), "; })");
        }
        if ((_v1768 == _v309)) {
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("({ ", _v1769), " "), _v1767), "; "), _v1720(_v1254, _v1767, _v507(_v541(_v542)))), _v1767), "; })");
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("({ ", _v1769), " "), _v1767), " = 0; "), _v1720(_v1254, _v1767, _v507(_v541(_v542)))), _v1767), "; })");
    }
    if ((_v1686 == _v239)) {
        _v426 _v1001 = _v705(_v542);
        bkr_i64 _v399 = _v707(_v542);
        bkr_str _v1770 = _v1708(_v1254, _v1001);
        if ((bkr_str_eq(_v1770, "0") || (_v399 <= 0))) {
            return "{ 0 }";
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{ [0 ... ", int_to_string((_v399 - 1))), "] = "), _v1770), " }");
    }
    if ((_v1686 == _v252)) {
        _v434 _v995 = _v702(_v542);
        bkr_str _v1196 = "{";
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v907(_v995))) {
            if ((_v1172 > 0)) {
                _v1196 = bkr_str_concat(_v1196, ", ");
            }
            _v1196 = bkr_str_concat(_v1196, _v1708(_v1254, _v538(_v910(_v995, _v1172))));
            _v1172 = (_v1172 + 1);
        }
        return bkr_str_concat(_v1196, "}");
    }
    if ((_v1686 == _v257)) {
        bkr_str _v1771 = _v1653(_v1254, _v725(_v542));
        _v435 _v1008 = _v728(_v542);
        _v434 _v1009 = _v731(_v542);
        bkr_i64 _v403 = _v1006(_v542);
        bkr_str _v1196 = bkr_str_concat(bkr_str_concat("(", _v1771), "){");
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v916(_v1008))) {
            if ((_v1172 > 0)) {
                _v1196 = bkr_str_concat(_v1196, ", ");
            }
            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, "."), _v1653(_v1254, _v918(_v1008, _v1172))), " = "), _v1708(_v1254, _v538(_v910(_v1009, _v1172))));
            _v1172 = (_v1172 + 1);
        }
        if ((_v403 != 0)) {
            bkr_str _v1772 = _v1708(_v1254, _v538(_v403));
            bkr_i64 _v1755 = _v725(_v542);
            bkr_i64 _v1773 = _v1568(_v1254);
            if (_v526(_v1773)) {
                _v341 _v1774 = _v507(_v1773);
                _v434 _v1775 = _v899(_v1774);
                bkr_i64 _v1776 = 0;
                while ((_v1776 < _v907(_v1775))) {
                    _v428 _v1777 = _v914(_v1775, _v1776);
                    if (((_v569(_v1777) == _v254) && (_v887(_v1777) == _v1755))) {
                        _v434 _v1778 = _v890(_v1777);
                        bkr_i64 _v1779 = 0;
                        while ((_v1779 < _v907(_v1778))) {
                            _v341 _v1780 = _v913(_v1778, _v1779);
                            bkr_i64 _v1682 = _v892(_v1780);
                            bkr_bool _v1781 = BKR_FALSE;
                            bkr_i64 _v1782 = 0;
                            while ((_v1782 < _v916(_v1008))) {
                                if ((_v918(_v1008, _v1782) == _v1682)) {
                                    _v1781 = BKR_TRUE;
                                }
                                _v1782 = (_v1782 + 1);
                            }
                            if ((!_v1781)) {
                                if ((_v1172 > 0)) {
                                    _v1196 = bkr_str_concat(_v1196, ", ");
                                }
                                _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, "."), _v1653(_v1254, _v1682)), " = ("), _v1772), ")."), _v1653(_v1254, _v1682));
                                _v1172 = (_v1172 + 1);
                            }
                            _v1779 = (_v1779 + 1);
                        }
                    }
                    _v1776 = (_v1776 + 1);
                }
            }
        }
        return bkr_str_concat(_v1196, "}");
    }
    if ((_v1686 == _v245)) {
        bkr_i64 _v355 = _v663(_v542);
        bkr_i64 _v425 = _v1577(_v1254);
        bkr_str _v1656 = _v1641(_v425, _v355);
        if (bkr_str_eq(_v1656, "None")) {
            return "0";
        }
        return _v1653(_v1254, _v355);
    }
    if ((_v1686 == _v253)) {
        _v426 _v1038 = _v538(_v712(_v542));
        _v426 _v1446 = _v538(_v715(_v542));
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1708(_v1254, _v1038), "["), _v1708(_v1254, _v1446)), "]");
    }
    if ((_v1686 == _v256)) {
        _v426 _v1038 = _v538(_v720(_v542));
        bkr_i64 _v1045 = _v723(_v542);
        bkr_i64 _v425 = _v1577(_v1254);
        bkr_str _v1783 = _v1641(_v425, _v1045);
        if ((((bkr_str_eq(_v1783, "0") || bkr_str_eq(_v1783, "1")) || bkr_str_eq(_v1783, "2")) || bkr_str_eq(_v1783, "3"))) {
            bkr_bool _v1784 = (_v1669(_v1254, _v1038) == _v309);
            if (((!_v1784) && (_v545(_v1038) == _v245))) {
                if ((_v1612(_v1254, _v663(_v1038)) >= 0)) {
                    _v1784 = BKR_TRUE;
                }
            }
            if (_v1784) {
                return bkr_str_concat(bkr_str_concat(_v1708(_v1254, _v1038), "."), _v1653(_v1254, _v1045));
            }
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_tuple_get(", _v1708(_v1254, _v1038)), ", "), _v1783), ")");
        }
        if ((_v545(_v1038) == _v245)) {
            bkr_str _v1642 = _v1641(_v425, _v663(_v1038));
            bkr_i64 _v1690 = _v1643(_v1254, _v1642, _v1783);
            if ((_v1690 >= 0)) {
                return int_to_string(_v1690);
            }
        }
        return bkr_str_concat(bkr_str_concat(_v1708(_v1254, _v1038), "."), _v1653(_v1254, _v1045));
    }
    if ((_v1686 == _v242)) {
        bkr_i64 _v349 = _v672(_v542);
        _v426 _v1051 = _v538(_v675(_v542));
        _v426 _v1052 = _v538(_v678(_v542));
        if ((_v349 == _v176)) {
            if ((_v545(_v1052) == _v256)) {
                _v426 _v1038 = _v538(_v720(_v1052));
                bkr_i64 _v1045 = _v723(_v1052);
                bkr_i64 _v425 = _v1577(_v1254);
                if ((_v545(_v1038) == _v245)) {
                    bkr_str _v1642 = _v1641(_v425, _v663(_v1038));
                    bkr_str _v1644 = _v1641(_v425, _v1045);
                    bkr_i64 _v1690 = _v1643(_v1254, _v1642, _v1644);
                    if (((_v1690 >= 0) && _v1649(_v1254, _v1642))) {
                        if ((_v545(_v1051) == _v242)) {
                            bkr_i64 _v1785 = _v672(_v1051);
                            if ((_v1785 == _v178)) {
                                _v426 _v1786 = _v538(_v675(_v1051));
                                bkr_str _v1787 = _v1708(_v1254, _v1786);
                                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_enum_payload1(", int_to_string(_v1690)), ", (bkr_i64)(intptr_t)("), _v1787), "))");
                            }
                            if ((_v1785 == _v176)) {
                                _v426 _v1788 = _v538(_v675(_v1051));
                                _v426 _v1789 = _v538(_v678(_v1051));
                                if (((_v545(_v1788) == _v242) && (_v545(_v1789) == _v242))) {
                                    _v426 _v1790 = _v538(_v675(_v1788));
                                    _v426 _v1791 = _v538(_v675(_v1789));
                                    bkr_str _v1792 = _v1708(_v1254, _v1790);
                                    bkr_str _v1793 = _v1708(_v1254, _v1791);
                                    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_enum_payload2(", int_to_string(_v1690)), ", (bkr_i64)(intptr_t)("), _v1792), "), (bkr_i64)(intptr_t)("), _v1793), "))");
                                }
                            }
                        }
                    }
                }
            }
        }
        if (((_v349 == _v166) || (_v349 == _v167))) {
            bkr_i64 _v1691 = _v1669(_v1254, _v1051);
            bkr_i64 _v1692 = _v1669(_v1254, _v1052);
            if (((_v1691 == _v306) || (_v1692 == _v306))) {
                bkr_str _v1794 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_eq(", _v1708(_v1254, _v1051)), ", "), _v1708(_v1254, _v1052)), ")");
                if ((_v349 == _v167)) {
                    return bkr_str_concat(bkr_str_concat("(!", _v1794), ")");
                }
                return _v1794;
            }
        }
        if ((_v349 == _v161)) {
            bkr_i64 _v1691 = _v1669(_v1254, _v1051);
            bkr_i64 _v1692 = _v1669(_v1254, _v1052);
            if (((_v1691 == _v306) || (_v1692 == _v306))) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_concat(", _v1708(_v1254, _v1051)), ", "), _v1708(_v1254, _v1052)), ")");
            }
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1708(_v1254, _v1051)), _v1654(_v349)), _v1708(_v1254, _v1052)), ")");
    }
    if ((_v1686 == _v250)) {
        _v426 _v1057 = _v538(_v734(_v542));
        _v426 _v1418 = _v538(_v737(_v542));
        _v426 _v1419 = _v538(_v740(_v542));
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("(", _v1708(_v1254, _v1057)), " ? "), _v1708(_v1254, _v1418)), " : "), _v1708(_v1254, _v1419)), ")");
    }
    if ((_v1686 == _v240)) {
        _v426 _v1381 = _v538(_v778(_v542));
        bkr_str _v1795 = _v1620(_v1254, "_bkr_try");
        bkr_str _v1796 = _v1708(_v1254, _v1381);
        bkr_i64 _v1562 = _v1613(_v1254);
        bkr_i64 _v1797 = vec_len(_v1562);
        bkr_str _v1798 = "";
        if ((_v1797 > 0)) {
            _v1547 _v1799 = _v1551("", _v1577(_v1254));
            bkr_i64 _v1800 = (_v1797 - 1);
            while ((_v1800 >= 0)) {
                _v1801(_v1799, _v550(vec_get(_v1562, _v1800)));
                _v1800 = (_v1800 - 1);
            }
            bkr_i64 _v1552 = _v1570(_v1799);
            bkr_i64 _v1802 = 0;
            while ((_v1802 < vec_len(_v1552))) {
                _v1798 = bkr_str_concat(bkr_str_concat(_v1798, " "), vec_get(_v1552, _v1802));
                _v1802 = (_v1802 + 1);
            }
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("({ bkr_i64 ", _v1795), " = "), _v1796), "; if (bkr_try_is_err("), _v1795), ")) {"), _v1798), " return "), _v1795), "; } bkr_try_unwrap("), _v1795), "); })");
    }
    if ((_v1686 == _v241)) {
        _v426 _v1694 = _v538(_v782(_v542));
        _v346 _v1450 = _v517(_v783(_v542));
        bkr_i64 _v1803 = _v530(_v1450);
        bkr_str _v1716 = _v1650(_v1803);
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("((", _v1716), ")("), _v1708(_v1254, _v1694)), "))");
    }
    if ((_v1686 == _v243)) {
        bkr_i64 _v349 = _v682(_v542);
        _v426 _v1032 = _v538(_v685(_v542));
        if ((_v349 == _v174)) {
            return bkr_str_concat(bkr_str_concat("(!", _v1708(_v1254, _v1032)), ")");
        }
        if ((_v349 == _v162)) {
            return bkr_str_concat(bkr_str_concat("(-", _v1708(_v1254, _v1032)), ")");
        }
        return _v1708(_v1254, _v1032);
    }
    if ((_v1686 == _v258)) {
        return _v1752(_v1254, _v542);
    }
    if ((_v1686 == _v261)) {
        _v426 _v1022 = _v695(_v542);
        bkr_i64 _v1519 = (-1);
        if ((_v545(_v1022) == _v245)) {
            _v1519 = _v1612(_v1254, _v663(_v1022));
        }
        bkr_i64 _v425 = _v1577(_v1254);
        bkr_str _v1697 = "";
        if ((_v1519 >= 0)) {
            _v1697 = _v1641(_v425, _v1519);
        }
        bkr_str _v1698 = _v1641(_v425, _v697(_v542));
        bkr_str _v1439 = bkr_str_concat(bkr_str_concat(_v1697, "::"), _v1698);
        bkr_i64 _v1699 = _v1578(_v1254, _v1439);
        bkr_str _v1804 = _v1653(_v1254, _v1699);
        bkr_str _v1805 = _v1708(_v1254, _v1022);
        _v434 _v1016 = _v699(_v542);
        bkr_i64 _v1806 = _v907(_v1016);
        bkr_str _v1807 = _v1805;
        bkr_i64 _v1645 = 0;
        while ((_v1645 < _v1806)) {
            _v1807 = bkr_str_concat(bkr_str_concat(_v1807, ", "), _v1708(_v1254, _v538(_v910(_v1016, _v1645))));
            _v1645 = (_v1645 + 1);
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1804, "("), _v1807), ")");
    }
    if ((_v1686 == _v244)) {
        bkr_i64 _v355 = _v689(_v542);
        _v434 _v1016 = _v692(_v542);
        bkr_i64 _v1806 = _v907(_v1016);
        if (_v1676(_v1254, _v355)) {
            bkr_str _v1808 = _v1653(_v1254, _v355);
            bkr_str _v1196 = bkr_str_concat(bkr_str_concat("(", _v1808), "){");
            bkr_i64 _v1172 = 0;
            while ((_v1172 < _v1806)) {
                if ((_v1172 > 0)) {
                    _v1196 = bkr_str_concat(_v1196, ", ");
                }
                _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, "."), _v1653(_v1254, _v1578(_v1254, int_to_string(_v1172)))), " = "), _v1708(_v1254, _v538(_v910(_v1016, _v1172))));
                _v1172 = (_v1172 + 1);
            }
            return bkr_str_concat(_v1196, "}");
        }
        bkr_i64 _v425 = _v1577(_v1254);
        bkr_str _v1656 = _v1641(_v425, _v355);
        if ((bkr_str_eq(_v1656, "panic") && (_v1806 == 1))) {
            bkr_str _v1809 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_panic((bkr_str)(intptr_t)(", _v1809), "))");
        }
        if ((bkr_str_eq(_v1656, "assert") && (_v1806 == 1))) {
            bkr_str _v1810 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1811 = from_char_code(34);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_assert(", _v1810), ", "), _v1811), "assertion failed"), _v1811), ")");
        }
        if ((bkr_str_eq(_v1656, "assert") && (_v1806 == 2))) {
            bkr_str _v1812 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1813 = _v1708(_v1254, _v538(_v910(_v1016, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_assert(", _v1812), ", (bkr_str)(intptr_t)("), _v1813), "))");
        }
        if ((bkr_str_eq(_v1656, "Some") && (_v1806 == 1))) {
            return bkr_str_concat(bkr_str_concat("(((", _v1708(_v1254, _v538(_v910(_v1016, 0)))), ") << 1) | 1)");
        }
        if ((bkr_str_eq(_v1656, "len") && (_v1806 == 1))) {
            _v426 _v1814 = _v538(_v910(_v1016, 0));
            bkr_i64 _v1815 = _v545(_v1814);
            if ((_v1815 == _v245)) {
                bkr_i64 _v1707 = _v1629(_v1254, _v663(_v1814));
                if ((_v1707 >= 0)) {
                    return int_to_string(_v1707);
                }
            }
            if ((_v1815 == _v252)) {
                _v434 _v995 = _v702(_v1814);
                return int_to_string(_v907(_v995));
            }
            if ((_v1815 == _v239)) {
                return int_to_string(_v707(_v1814));
            }
            return bkr_str_concat(bkr_str_concat("bkr_len((bkr_str)(intptr_t)(", _v1708(_v1254, _v1814)), "))");
        }
        if ((bkr_str_eq(_v1656, "strlen") && (_v1806 == 1))) {
            _v426 _v1816 = _v538(_v910(_v1016, 0));
            return bkr_str_concat(bkr_str_concat("bkr_len((bkr_str)(intptr_t)(", _v1708(_v1254, _v1816)), "))");
        }
        if (((bkr_str_eq(_v1656, "result_ok") || bkr_str_eq(_v1656, "Ok")) && (_v1806 == 1))) {
            bkr_str _v1817 = _v1762(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_result_ok(", _v1817), ")");
        }
        if (((bkr_str_eq(_v1656, "result_err") || bkr_str_eq(_v1656, "Err")) && (_v1806 == 1))) {
            bkr_str _v1818 = _v1762(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_result_err(", _v1818), ")");
        }
        if ((bkr_str_eq(_v1656, "hashmap_get_opt") && (_v1806 == 2))) {
            bkr_str _v1819 = _v1762(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1820 = _v1762(_v1254, _v538(_v910(_v1016, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_hashmap_get_opt(", _v1819), ", "), _v1820), ")");
        }
        if ((bkr_str_eq(_v1656, "vec_get_opt") && (_v1806 == 2))) {
            bkr_str _v1702 = _v1762(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1821 = _v1762(_v1254, _v538(_v910(_v1016, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_vec_get_opt(", _v1702), ", "), _v1821), ")");
        }
        if ((bkr_str_eq(_v1656, "vec_pop_opt") && (_v1806 == 1))) {
            bkr_str _v1822 = _v1762(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_vec_pop_opt(", _v1822), ")");
        }
        if ((bkr_str_eq(_v1656, "vec_contains") && (_v1806 == 2))) {
            bkr_str _v1823 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            _v426 _v1824 = _v538(_v910(_v1016, 1));
            bkr_i64 _v1825 = _v1669(_v1254, _v1824);
            bkr_str _v1826 = _v1762(_v1254, _v1824);
            if ((_v1825 == _v306)) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("vec_contains_str(", _v1823), ", "), _v1826), ")");
            }
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("vec_contains(", _v1823), ", "), _v1826), ")");
        }
        if ((bkr_str_eq(_v1656, "read_file_result") && (_v1806 == 1))) {
            bkr_str _v1787 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_read_file_result((bkr_str)(intptr_t)(", _v1787), "))");
        }
        if ((bkr_str_eq(_v1656, "write_file_result") && (_v1806 == 2))) {
            bkr_str _v1827 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1828 = _v1708(_v1254, _v538(_v910(_v1016, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_write_file_result((bkr_str)(intptr_t)(", _v1827), "), (bkr_str)(intptr_t)("), _v1828), "))");
        }
        if ((bkr_str_eq(_v1656, "parse_int_result") && (_v1806 == 1))) {
            bkr_str _v1829 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_parse_int_result((bkr_str)(intptr_t)(", _v1829), "))");
        }
        if ((bkr_str_eq(_v1656, "str_index_of") && (_v1806 == 2))) {
            bkr_str _v1829 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1830 = _v1708(_v1254, _v538(_v910(_v1016, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_index_of((bkr_str)(intptr_t)(", _v1829), "), (bkr_str)(intptr_t)("), _v1830), "))");
        }
        if ((bkr_str_eq(_v1656, "str_replace") && (_v1806 == 3))) {
            bkr_str _v1829 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1831 = _v1708(_v1254, _v538(_v910(_v1016, 1)));
            bkr_str _v1832 = _v1708(_v1254, _v538(_v910(_v1016, 2)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_replace((bkr_str)(intptr_t)(", _v1829), "), (bkr_str)(intptr_t)("), _v1831), "), (bkr_str)(intptr_t)("), _v1832), "))");
        }
        if ((bkr_str_eq(_v1656, "str_split") && (_v1806 == 2))) {
            bkr_str _v1829 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1833 = _v1708(_v1254, _v538(_v910(_v1016, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_split((bkr_str)(intptr_t)(", _v1829), "), (bkr_str)(intptr_t)("), _v1833), "))");
        }
        if ((bkr_str_eq(_v1656, "str_to_upper") && (_v1806 == 1))) {
            bkr_str _v1829 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_str_to_upper((bkr_str)(intptr_t)(", _v1829), "))");
        }
        if ((bkr_str_eq(_v1656, "str_to_lower") && (_v1806 == 1))) {
            bkr_str _v1829 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_str_to_lower((bkr_str)(intptr_t)(", _v1829), "))");
        }
        if ((bkr_str_eq(_v1656, "str_repeat") && (_v1806 == 2))) {
            bkr_str _v1829 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1828 = _v1762(_v1254, _v538(_v910(_v1016, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_str_repeat((bkr_str)(intptr_t)(", _v1829), "), "), _v1828), ")");
        }
        if ((bkr_str_eq(_v1656, "path_join") && (_v1806 == 2))) {
            bkr_str _v1834 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1835 = _v1708(_v1254, _v538(_v910(_v1016, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_path_join((bkr_str)(intptr_t)(", _v1834), "), (bkr_str)(intptr_t)("), _v1835), "))");
        }
        if ((bkr_str_eq(_v1656, "path_dir") && (_v1806 == 1))) {
            bkr_str _v1787 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_path_dir((bkr_str)(intptr_t)(", _v1787), "))");
        }
        if ((bkr_str_eq(_v1656, "path_base") && (_v1806 == 1))) {
            bkr_str _v1787 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_path_base((bkr_str)(intptr_t)(", _v1787), "))");
        }
        if ((bkr_str_eq(_v1656, "path_ext") && (_v1806 == 1))) {
            bkr_str _v1787 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_path_ext((bkr_str)(intptr_t)(", _v1787), "))");
        }
        if ((bkr_str_eq(_v1656, "path_is_abs") && (_v1806 == 1))) {
            bkr_str _v1787 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_path_is_abs((bkr_str)(intptr_t)(", _v1787), "))");
        }
        if ((bkr_str_eq(_v1656, "env_var") && (_v1806 == 1))) {
            bkr_str _v1836 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_env_var((bkr_str)(intptr_t)(", _v1836), "))");
        }
        if ((bkr_str_eq(_v1656, "env_get") && (_v1806 == 1))) {
            bkr_str _v1836 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_env_get((bkr_str)(intptr_t)(", _v1836), "))");
        }
        if ((bkr_str_eq(_v1656, "env_set") && (_v1806 == 2))) {
            bkr_str _v1836 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1702 = _v1708(_v1254, _v538(_v910(_v1016, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("bkr_env_set((bkr_str)(intptr_t)(", _v1836), "), (bkr_str)(intptr_t)("), _v1702), "))");
        }
        if ((bkr_str_eq(_v1656, "env_has") && (_v1806 == 1))) {
            bkr_str _v1836 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_env_has((bkr_str)(intptr_t)(", _v1836), "))");
        }
        if ((bkr_str_eq(_v1656, "time_now_ms") && (_v1806 == 0))) {
            return "bkr_time_now_ms()";
        }
        if ((bkr_str_eq(_v1656, "time_now_unix") && (_v1806 == 0))) {
            return "bkr_time_now_unix()";
        }
        if ((bkr_str_eq(_v1656, "runtime_version_major") && (_v1806 == 0))) {
            return "bkr_runtime_version_major()";
        }
        if ((bkr_str_eq(_v1656, "runtime_version_minor") && (_v1806 == 0))) {
            return "bkr_runtime_version_minor()";
        }
        if ((bkr_str_eq(_v1656, "runtime_version_patch") && (_v1806 == 0))) {
            return "bkr_runtime_version_patch()";
        }
        if ((bkr_str_eq(_v1656, "runtime_version_str") && (_v1806 == 0))) {
            return "bkr_runtime_version_str()";
        }
        if ((bkr_str_eq(_v1656, "vec_push") && (_v1806 == 2))) {
            bkr_str _v1823 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v387 = _v1762(_v1254, _v538(_v910(_v1016, 1)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("vec_push(", _v1823), ", "), _v387), ")");
        }
        if ((bkr_str_eq(_v1656, "vec_set") && (_v1806 == 3))) {
            bkr_str _v1837 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            bkr_str _v1036 = _v1708(_v1254, _v538(_v910(_v1016, 1)));
            bkr_str _v1838 = _v1762(_v1254, _v538(_v910(_v1016, 2)));
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("vec_set(", _v1837), ", "), _v1036), ", "), _v1838), ")");
        }
        if ((bkr_str_eq(_v1656, "hashmap_insert") && (_v1806 == 3))) {
            bkr_str _v1839 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            _v426 _v1840 = _v538(_v910(_v1016, 1));
            bkr_i64 _v1378 = _v1669(_v1254, _v1840);
            bkr_str _v1841 = _v1762(_v1254, _v1840);
            bkr_str _v1842 = _v1762(_v1254, _v538(_v910(_v1016, 2)));
            if ((_v1378 == _v306)) {
                return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("hashmap_insert_str(", _v1839), ", "), _v1841), ", "), _v1842), ")");
            }
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("hashmap_insert(", _v1839), ", "), _v1841), ", "), _v1842), ")");
        }
        if ((bkr_str_eq(_v1656, "hashmap_get") && (_v1806 == 2))) {
            bkr_str _v1839 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            _v426 _v1840 = _v538(_v910(_v1016, 1));
            bkr_str _v1841 = _v1762(_v1254, _v1840);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("hashmap_get(", _v1839), ", "), _v1841), ")");
        }
        if ((bkr_str_eq(_v1656, "hashmap_contains") && (_v1806 == 2))) {
            bkr_str _v1839 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            _v426 _v1840 = _v538(_v910(_v1016, 1));
            bkr_str _v1841 = _v1762(_v1254, _v1840);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("hashmap_contains(", _v1839), ", "), _v1841), ")");
        }
        if ((bkr_str_eq(_v1656, "hashmap_remove") && (_v1806 == 2))) {
            bkr_str _v1839 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            _v426 _v1840 = _v538(_v910(_v1016, 1));
            bkr_str _v1841 = _v1762(_v1254, _v1840);
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("hashmap_remove(", _v1839), ", "), _v1841), ")");
        }
        if ((bkr_str_eq(_v1656, "result_is_ok") && (_v1806 == 1))) {
            bkr_str _v1843 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_result_is_ok(", _v1843), ")");
        }
        if ((bkr_str_eq(_v1656, "result_is_err") && (_v1806 == 1))) {
            bkr_str _v1844 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_result_is_err(", _v1844), ")");
        }
        if ((bkr_str_eq(_v1656, "result_tag") && (_v1806 == 1))) {
            bkr_str _v1845 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            return bkr_str_concat(bkr_str_concat("bkr_result_tag(", _v1845), ")");
        }
        if ((((bkr_str_eq(_v1656, "result_unwrap") || bkr_str_eq(_v1656, "result_unwrap_err")) || bkr_str_eq(_v1656, "result_value")) && (_v1806 == 1))) {
            bkr_str _v1846 = _v1708(_v1254, _v538(_v910(_v1016, 0)));
            if (bkr_str_eq(_v1656, "result_unwrap")) {
                return bkr_str_concat(bkr_str_concat("bkr_result_unwrap(", _v1846), ")");
            }
            if (bkr_str_eq(_v1656, "result_unwrap_err")) {
                return bkr_str_concat(bkr_str_concat("bkr_result_unwrap_err(", _v1846), ")");
            }
            return bkr_str_concat(bkr_str_concat("bkr_result_value(", _v1846), ")");
        }
        bkr_str _v1363 = _v1653(_v1254, _v355);
        bkr_str _v1196 = "";
        if ((_v1635(_v1254, _v355) == _v315)) {
            _v1196 = bkr_str_concat(bkr_str_concat("((bkr_i64 (*)())", _v1363), ")(");
        } else {
            _v1196 = bkr_str_concat(_v1363, "(");
        }
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v1806)) {
            if ((_v1172 > 0)) {
                _v1196 = bkr_str_concat(_v1196, ", ");
            }
            _v1196 = bkr_str_concat(_v1196, _v1708(_v1254, _v538(_v910(_v1016, _v1172))));
            _v1172 = (_v1172 + 1);
        }
        return bkr_str_concat(_v1196, ")");
    }
    return "0";
}

bkr_i64 _v1847(bkr_i64 _v1254, bkr_i64 _v370) {
    _v1801(_v1564(_v1254), _v551(_v370));
    return _v1254;
}

_v1547 _v1801(_v1547 _v1254, _v427 _v554) {
    bkr_i64 _v1686 = _v556(_v554);
    if ((_v1686 == _v228)) {
        bkr_i64 _v355 = _v758(_v554);
        bkr_str _v1363 = _v1653(_v1254, _v355);
        bkr_i64 _v516 = _v761(_v554);
        bkr_i64 _v366 = _v764(_v554);
        if ((_v526(_v516) && (_v1662(_v517(_v516)) == _v308))) {
            bkr_i64 _v954 = _v1664(_v517(_v516));
            bkr_i64 _v1707 = _v1666(_v517(_v516));
            bkr_str _v1598 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1650(_v954), " "), _v1363), "["), int_to_string(_v1707)), "]");
            if (_v526(_v366)) {
                _v1598 = bkr_str_concat(bkr_str_concat(_v1598, " = "), _v1708(_v1254, _v538(_v366)));
            }
            _v1599(_v1254, bkr_str_concat(_v1598, ";"));
            _v1608(_v1254, _v355, _v954);
            _v1627(_v1254, _v355, _v954, _v1707);
            return _v1254;
        }
        if ((_v524(_v516) && _v526(_v366))) {
            _v426 _v1709 = _v538(_v366);
            bkr_i64 _v1710 = _v545(_v1709);
            if ((_v1710 == _v252)) {
                _v434 _v995 = _v702(_v1709);
                bkr_i64 _v1707 = _v907(_v995);
                if ((_v1707 > 0)) {
                    bkr_i64 _v954 = _v1669(_v1254, _v538(_v910(_v995, 0)));
                    bkr_str _v1598 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1650(_v954), " "), _v1363), "["), int_to_string(_v1707)), "] = "), _v1708(_v1254, _v1709));
                    _v1599(_v1254, bkr_str_concat(_v1598, ";"));
                    _v1608(_v1254, _v355, _v954);
                    _v1627(_v1254, _v355, _v954, _v1707);
                    return _v1254;
                }
            } else {
                if ((_v1710 == _v239)) {
                    bkr_i64 _v1707 = _v707(_v1709);
                    bkr_i64 _v954 = _v1669(_v1254, _v705(_v1709));
                    bkr_str _v1598 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1650(_v954), " "), _v1363), "["), int_to_string(_v1707)), "] = "), _v1708(_v1254, _v1709));
                    _v1599(_v1254, bkr_str_concat(_v1598, ";"));
                    _v1608(_v1254, _v355, _v954);
                    _v1627(_v1254, _v355, _v954, _v1707);
                    return _v1254;
                }
            }
        }
        bkr_i64 _v319 = _v303;
        bkr_i64 _v1519 = (-1);
        if (_v526(_v516)) {
            _v319 = _v1662(_v517(_v516));
            if ((_v319 == _v309)) {
                _v1519 = _v532(_v517(_v516));
            }
            if ((_v319 == _v310)) {
                bkr_i64 _v1703 = _v533(_v517(_v516));
                if (((_v1703 != _v316) && (_v1703 != 0))) {
                    _v1627(_v1254, _v355, _v1703, 0);
                }
            }
        } else {
            if (_v526(_v366)) {
                bkr_i64 _v1711 = _v1672(_v1254, _v366);
                if (((_v1711 != _v316) && (_v1711 != _v307))) {
                    _v319 = _v1711;
                }
                _v426 _v1709 = _v538(_v366);
                if ((_v545(_v1709) == _v257)) {
                    _v319 = _v309;
                    _v1519 = _v725(_v1709);
                } else {
                    if ((_v545(_v1709) == _v244)) {
                        bkr_i64 _v1712 = _v689(_v1709);
                        if (_v1676(_v1254, _v1712)) {
                            _v319 = _v309;
                            _v1519 = _v1712;
                        } else {
                            _v346 _v1695 = _v1684(_v1254, _v1712);
                            if ((_v525(_v1695) && (_v530(_v1695) == _v309))) {
                                _v319 = _v309;
                                _v1519 = _v532(_v1695);
                            }
                        }
                    } else {
                        if ((_v545(_v1709) == _v245)) {
                            bkr_i64 _v1713 = _v1612(_v1254, _v1025(_v1709));
                            if ((_v1713 >= 0)) {
                                _v319 = _v309;
                                _v1519 = _v1713;
                            }
                        } else {
                            if ((_v545(_v1709) == _v227)) {
                                _v429 _v583 = _v579(_v541(_v1709));
                                bkr_i64 _v399 = _v590(_v583);
                                if ((_v399 > 0)) {
                                    _v427 _v1687 = _v1111(_v583, (_v399 - 1));
                                    if ((_v556(_v1687) == _v232)) {
                                        _v426 _v1714 = _v538(_v861(_v1687));
                                        bkr_i64 _v1715 = _v545(_v1714);
                                        if ((_v1715 == _v257)) {
                                            _v319 = _v309;
                                            _v1519 = _v725(_v1714);
                                        } else {
                                            if ((_v1715 == _v245)) {
                                                bkr_i64 _v1713 = _v1612(_v1254, _v663(_v1714));
                                                if ((_v1713 >= 0)) {
                                                    _v319 = _v309;
                                                    _v1519 = _v1713;
                                                }
                                            } else {
                                                if (((_v1715 == _v244) && _v1676(_v1254, _v689(_v1714)))) {
                                                    _v319 = _v309;
                                                    _v1519 = _v689(_v1714);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        bkr_str _v1716 = _v1650(_v319);
        if (_v526(_v516)) {
            _v1716 = _v1652(_v1254, _v517(_v516));
        } else {
            if (((_v319 == _v309) && (_v1519 >= 0))) {
                if (_v1639(_v1254, _v1519)) {
                    _v1716 = "bkr_i64";
                } else {
                    _v1716 = _v1653(_v1254, _v1519);
                }
            }
        }
        if (bkr_str_eq(_v1716, "void")) {
            _v1716 = "bkr_unit";
        }
        bkr_str _v1598 = bkr_str_concat(bkr_str_concat(_v1716, " "), _v1363);
        if (_v526(_v366)) {
            _v1598 = bkr_str_concat(bkr_str_concat(_v1598, " = "), _v1717(_v1254, _v516, _v538(_v366)));
        }
        _v1599(_v1254, bkr_str_concat(_v1598, ";"));
        if ((_v1519 >= 0)) {
            if (_v1639(_v1254, _v1519)) {
                _v1608(_v1254, _v355, _v303);
            } else {
                _v1610(_v1254, _v355, _v319, _v1519);
            }
        } else {
            _v1608(_v1254, _v355, _v319);
        }
        return _v1254;
    }
    if ((_v1686 == _v238)) {
        bkr_i64 _v1848 = _v773(_v554);
        _v1614(_v1254, _v1848);
        return _v1254;
    }
    if ((_v1686 == _v229)) {
        bkr_i64 _v368 = _v769(_v554);
        bkr_i64 _v1562 = _v1613(_v1254);
        bkr_i64 _v1797 = vec_len(_v1562);
        bkr_str _v1849 = _v1616(_v1254);
        if (bkr_str_eq(_v1849, "void")) {
            if (_v526(_v368)) {
                _v426 _v542 = _v538(_v368);
                bkr_i64 _v1850 = _v545(_v542);
                if ((_v1850 != _v246)) {
                    _v1599(_v1254, bkr_str_concat(_v1708(_v1254, _v542), ";"));
                }
            }
            bkr_i64 _v1800 = (_v1797 - 1);
            while ((_v1800 >= 0)) {
                _v1801(_v1254, _v550(vec_get(_v1562, _v1800)));
                _v1800 = (_v1800 - 1);
            }
            _v1599(_v1254, "return;");
            return _v1254;
        }
        if ((_v1797 > 0)) {
            if (_v526(_v368)) {
                bkr_str _v1851 = _v1620(_v1254, "_bkr_ret");
                bkr_str _v1146 = _v1616(_v1254);
                if ((bkr_str_eq(_v1146, "") || bkr_str_eq(_v1146, "void"))) {
                    _v1146 = "bkr_i64";
                }
                _v1599(_v1254, bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1146, " "), _v1851), " = "), _v1708(_v1254, _v538(_v368))), ";"));
                bkr_i64 _v1800 = (_v1797 - 1);
                while ((_v1800 >= 0)) {
                    _v1801(_v1254, _v550(vec_get(_v1562, _v1800)));
                    _v1800 = (_v1800 - 1);
                }
                _v1599(_v1254, bkr_str_concat(bkr_str_concat("return ", _v1851), ";"));
            } else {
                bkr_i64 _v1800 = (_v1797 - 1);
                while ((_v1800 >= 0)) {
                    _v1801(_v1254, _v550(vec_get(_v1562, _v1800)));
                    _v1800 = (_v1800 - 1);
                }
                _v1599(_v1254, "return;");
            }
        } else {
            if (_v526(_v368)) {
                _v1599(_v1254, bkr_str_concat(bkr_str_concat("return ", _v1708(_v1254, _v538(_v368))), ";"));
            } else {
                _v1599(_v1254, "return;");
            }
        }
        return _v1254;
    }
    if ((_v1686 == _v230)) {
        _v426 _v1057 = _v538(_v828(_v554));
        _v429 _v1120 = _v830(_v554);
        bkr_i64 _v377 = _v833(_v554);
        _v1599(_v1254, bkr_str_concat(bkr_str_concat("if (", _v1708(_v1254, _v1057)), ") {"));
        _v1602(_v1254);
        _v1852(_v1254, _v1120);
        _v1604(_v1254);
        if (_v526(_v377)) {
            _v1599(_v1254, "} else {");
            _v1602(_v1254);
            _v1852(_v1254, _v579(_v377));
            _v1604(_v1254);
        }
        _v1599(_v1254, "}");
        return _v1254;
    }
    if ((_v1686 == _v231)) {
        _v426 _v1057 = _v538(_v850(_v554));
        _v429 _v1127 = _v852(_v554);
        _v1599(_v1254, bkr_str_concat(bkr_str_concat("while (", _v1708(_v1254, _v1057)), ") {"));
        _v1602(_v1254);
        _v1852(_v1254, _v1127);
        _v1604(_v1254);
        _v1599(_v1254, "}");
        return _v1254;
    }
    if ((_v1686 == _v236)) {
        bkr_i64 _v355 = _v835(_v554);
        bkr_str _v1363 = _v1653(_v1254, _v355);
        _v426 _v1853 = _v538(_v838(_v554));
        _v426 _v1854 = _v538(_v841(_v554));
        bkr_i64 _v383 = _v843(_v554);
        _v429 _v1127 = _v845(_v554);
        bkr_str _v1794 = "<";
        if ((_v383 != 0)) {
            _v1794 = "<=";
        }
        _v1599(_v1254, bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("for (bkr_i64 ", _v1363), " = "), _v1708(_v1254, _v1853)), "; "), _v1363), " "), _v1794), " "), _v1708(_v1254, _v1854)), "; "), _v1363), " = "), _v1363), " + 1) {"));
        _v1602(_v1254);
        _v1608(_v1254, _v355, _v303);
        _v1852(_v1254, _v1127);
        _v1604(_v1254);
        _v1599(_v1254, "}");
        return _v1254;
    }
    if ((_v1686 == _v237)) {
        _v429 _v1127 = _v847(_v554);
        _v1599(_v1254, "while (BKR_TRUE) {");
        _v1602(_v1254);
        _v1852(_v1254, _v1127);
        _v1604(_v1254);
        _v1599(_v1254, "}");
        return _v1254;
    }
    if ((_v1686 == _v233)) {
        _v426 _v1098 = _v538(_v855(_v554));
        _v426 _v1099 = _v538(_v858(_v554));
        _v1599(_v1254, bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1708(_v1254, _v1098), " = "), _v1708(_v1254, _v1099)), ";"));
        return _v1254;
    }
    if ((_v1686 == _v232)) {
        _v426 _v542 = _v538(_v861(_v554));
        _v1599(_v1254, bkr_str_concat(_v1708(_v1254, _v542), ";"));
        return _v1254;
    }
    if ((_v1686 == _v234)) {
        _v1599(_v1254, "break;");
        return _v1254;
    }
    if ((_v1686 == _v235)) {
        _v1599(_v1254, "continue;");
        return _v1254;
    }
    if ((_v1686 == _v227)) {
        _v1852(_v1254, _v579(_v553(_v554)));
        return _v1254;
    }
    return _v1254;
}

bkr_str _v1766(bkr_str _v1656) {
    bkr_str _v1811 = from_char_code(34);
    bkr_str _v1855 = from_char_code(92);
    bkr_str _v1856 = "";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < bkr_len((bkr_str)(intptr_t)(_v1656)))) {
        bkr_str _v1857 = char_at(_v1656, _v1172);
        bkr_i64 _v1859 = char_code(_v1857);
        if ((_v1859 == 10)) {
            _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), "n");
        } else {
            if ((_v1859 == 13)) {
                _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), "r");
            } else {
                if ((_v1859 == 9)) {
                    _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), "t");
                } else {
                    if ((_v1859 == 34)) {
                        _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), _v1811);
                    } else {
                        if ((_v1859 == 92)) {
                            _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), _v1855);
                        } else {
                            _v1856 = bkr_str_concat(_v1856, _v1857);
                        }
                    }
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(bkr_str_concat(_v1811, _v1856), _v1811);
}

bkr_i64 _v1861(bkr_i64 _v1254, bkr_i64 _v578) {
    _v1852(_v1564(_v1254), _v580(_v578));
    return _v1254;
}

_v1547 _v1852(_v1547 _v1254, _v429 _v583) {
    bkr_i64 _v1172 = 0;
    bkr_i64 _v399 = _v590(_v583);
    while ((_v1172 < _v399)) {
        _v1801(_v1254, _v1111(_v583, _v1172));
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_str _v1862(bkr_i64 _v1254, bkr_i64 _v930) {
    return _v1863(_v1564(_v1254), _v560(_v930));
}

bkr_str _v1863(_v1547 _v1254, _v428 _v1530) {
    bkr_str _v1363 = _v1653(_v1254, _v869(_v1530));
    bkr_i64 _v1864 = _v875(_v1530);
    bkr_str _v1146 = "void";
    if (_v526(_v1864)) {
        _v1146 = _v1652(_v1254, _v517(_v1864));
    }
    bkr_str _v1865 = "";
    _v434 _v1145 = _v872(_v1530);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1145))) {
        _v341 _v1523 = _v913(_v1145, _v1172);
        bkr_str _v1866 = _v1653(_v1254, _v863(_v1523));
        bkr_str _v1867 = _v1652(_v1254, _v867(_v1523));
        if ((_v1172 > 0)) {
            _v1865 = bkr_str_concat(_v1865, ", ");
        }
        _v1865 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1865, _v1867), " "), _v1866);
        _v1172 = (_v1172 + 1);
    }
    if (bkr_str_eq(_v1865, "")) {
        _v1865 = "void";
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1146, " "), _v1363), "("), _v1865), ")");
}

bkr_i64 _v1868(bkr_i64 _v1254, bkr_i64 _v930) {
    _v1869(_v1564(_v1254), _v560(_v930));
    return _v1254;
}

_v1547 _v1869(_v1547 _v1254, _v428 _v1530) {
    _v1599(_v1254, bkr_str_concat(_v1863(_v1254, _v1530), ";"));
    return _v1254;
}

bkr_i64 _v1870(bkr_i64 _v1254, bkr_i64 _v930) {
    _v1871(_v1564(_v1254), _v560(_v930));
    return _v1254;
}

_v1547 _v1871(_v1547 _v1254, _v428 _v1530) {
    _v1606(_v1254);
    bkr_i64 _v1864 = _v875(_v1530);
    bkr_str _v1872 = "void";
    if (_v526(_v1864)) {
        _v1872 = _v1652(_v1254, _v517(_v1864));
    }
    _v1617(_v1254, _v1872);
    _v434 _v1145 = _v872(_v1530);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1145))) {
        _v341 _v1523 = _v913(_v1145, _v1172);
        _v346 _v1873 = _v867(_v1523);
        bkr_i64 _v1874 = _v1662(_v1873);
        if ((_v1874 == _v309)) {
            bkr_i64 _v1713 = _v532(_v1873);
            if (_v1639(_v1254, _v1713)) {
                _v1608(_v1254, _v863(_v1523), _v303);
            } else {
                _v1610(_v1254, _v863(_v1523), _v1874, _v1713);
            }
        } else {
            _v1608(_v1254, _v863(_v1523), _v1874);
        }
        if ((_v1874 == _v310)) {
            bkr_i64 _v1703 = _v533(_v1873);
            if (((_v1703 != _v316) && (_v1703 != 0))) {
                _v1627(_v1254, _v863(_v1523), _v1703, 0);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    _v429 _v1127 = _v877(_v1530);
    _v1599(_v1254, bkr_str_concat(_v1863(_v1254, _v1530), " {"));
    _v1602(_v1254);
    _v1852(_v1254, _v1127);
    bkr_i64 _v399 = _v590(_v1127);
    bkr_bool _v1875 = BKR_FALSE;
    if ((_v399 > 0)) {
        _v427 _v1687 = _v1111(_v1127, (_v399 - 1));
        if ((_v556(_v1687) == _v229)) {
            _v1875 = BKR_TRUE;
        }
    }
    bkr_i64 _v1562 = _v1613(_v1254);
    bkr_i64 _v1797 = vec_len(_v1562);
    if (((!_v1875) && (_v1797 > 0))) {
        bkr_i64 _v1800 = (_v1797 - 1);
        while ((_v1800 >= 0)) {
            _v1801(_v1254, _v550(vec_get(_v1562, _v1800)));
            _v1800 = (_v1800 - 1);
        }
    }
    _v1604(_v1254);
    _v1599(_v1254, "}");
    _v1599(_v1254, "");
    return _v1254;
}

bkr_i64 _v1876(bkr_i64 _v1254, bkr_i64 _v1877) {
    _v1878(_v1564(_v1254), _v560(_v1877));
    return _v1254;
}

_v1547 _v1878(_v1547 _v1254, _v428 _v1533) {
    bkr_i64 _v355 = _v879(_v1533);
    bkr_str _v1363 = _v1653(_v1254, _v355);
    bkr_i64 _v516 = _v882(_v1533);
    bkr_i64 _v387 = _v885(_v1533);
    bkr_i64 _v319 = _v303;
    if (_v526(_v516)) {
        _v319 = _v1662(_v517(_v516));
    } else {
        if (_v526(_v387)) {
            bkr_i64 _v1879 = _v1672(_v1254, _v387);
            if (((_v1879 != _v316) && (_v1879 != _v307))) {
                _v319 = _v1879;
            }
        }
    }
    bkr_str _v1716 = _v1650(_v319);
    bkr_str _v1880 = "0";
    if (_v526(_v387)) {
        _v1880 = _v1708(_v1254, _v538(_v387));
    }
    _v1599(_v1254, bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("static const ", _v1716), " "), _v1363), " = "), _v1880), ";"));
    _v1625(_v1254, _v355, _v319);
    return _v1254;
}

bkr_i64 _v1881(bkr_i64 _v1254, bkr_i64 _v933) {
    _v1882(_v1564(_v1254), _v560(_v933));
    return _v1254;
}

_v1547 _v1882(_v1547 _v1254, _v428 _v1539) {
    bkr_str _v1363 = _v1653(_v1254, _v887(_v1539));
    _v1599(_v1254, bkr_str_concat(bkr_str_concat("typedef struct ", _v1363), " {"));
    _v1602(_v1254);
    _v434 _v1162 = _v890(_v1539);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1162))) {
        _v341 _v1447 = _v913(_v1162, _v1172);
        bkr_str _v1045 = _v1653(_v1254, _v892(_v1447));
        _v346 _v1883 = _v896(_v1447);
        if ((_v530(_v1883) == _v308)) {
            bkr_i64 _v954 = _v533(_v1883);
            bkr_i64 _v1707 = _v534(_v1883);
            _v1599(_v1254, bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1650(_v954), " "), _v1045), "["), int_to_string(_v1707)), "];"));
        } else {
            _v1599(_v1254, bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1652(_v1254, _v1883), " "), _v1045), ";"));
        }
        _v1172 = (_v1172 + 1);
    }
    _v1604(_v1254);
    _v1599(_v1254, bkr_str_concat(bkr_str_concat("} ", _v1363), ";"));
    _v1599(_v1254, "");
    return _v1254;
}

bkr_i64 _v1884(bkr_i64 _v1254, bkr_i64 _v0) {
    _v1885(_v1564(_v1254), _v477(_v0));
    return _v1254;
}

_v1547 _v1885(_v1547 _v1254, _v341 _v1546) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v254)) {
            _v1882(_v1254, _v563);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v1886(bkr_i64 _v1254, bkr_i64 _v0) {
    _v1887(_v1564(_v1254), _v477(_v0));
    return _v1254;
}

_v1547 _v1887(_v1547 _v1254, _v341 _v1546) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v224)) {
            bkr_i64 _v1864 = _v875(_v563);
            bkr_i64 _v319 = _v307;
            if (_v526(_v1864)) {
                _v319 = _v1662(_v517(_v1864));
            }
            _v1623(_v1254, _v869(_v563), _v319);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v1888(bkr_i64 _v1254, bkr_i64 _v0) {
    _v1889(_v1564(_v1254), _v477(_v0));
    return _v1254;
}

_v1547 _v1889(_v1547 _v1254, _v341 _v1546) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v249)) {
            _v1878(_v1254, _v563);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

_v1547 _v1890(_v1547 _v1254, _v341 _v1546) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v260)) {
            bkr_i64 _v355 = _v1180(_v563);
            bkr_i64 _v421 = _v1181(_v563);
            _v346 _v1098 = _v517(_v421);
            bkr_str _v1891 = _v1652(_v1254, _v1098);
            bkr_str _v1892 = _v1653(_v1254, _v355);
            _v1599(_v1254, bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("typedef ", _v1891), " "), _v1892), ";"));
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v1893(bkr_i64 _v1254, bkr_i64 _v0) {
    _v1894(_v1564(_v1254), _v477(_v0));
    return _v1254;
}

_v1547 _v1894(_v1547 _v1254, _v341 _v1546) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v224)) {
            _v1869(_v1254, _v563);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v1895(bkr_i64 _v1254, bkr_i64 _v0) {
    _v1896(_v1564(_v1254), _v477(_v0));
    return _v1254;
}

_v1547 _v1896(_v1547 _v1254, _v341 _v1546) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v224)) {
            _v1871(_v1254, _v563);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_str _v1897(bkr_i64 _v0) {
    return _v1898(_v477(_v0));
}

bkr_str _v1898(_v341 _v1546) {
    bkr_i64 _v425 = _v904(_v1546);
    bkr_str _v1549 = _v1657(_v425, _v664(_v1546));
    _v1547 _v1254 = _v1551(_v1549, _v425);
    _v1565(_v1254, _v508(_v1546));
    _v1599(_v1254, "/* Generated by Bunker Compiler */");
    _v1599(_v1254, "#define BKR_REQUIRED_RUNTIME_ABI_MAJOR 1");
    bkr_str _v1811 = from_char_code(34);
    _v1599(_v1254, bkr_str_concat(bkr_str_concat(bkr_str_concat("#include ", _v1811), "runtime.h"), _v1811));
    _v1599(_v1254, "");
    _v1890(_v1254, _v1546);
    _v1885(_v1254, _v1546);
    _v1887(_v1254, _v1546);
    _v1889(_v1254, _v1546);
    _v1599(_v1254, "");
    _v1894(_v1254, _v1546);
    _v1599(_v1254, "");
    _v1896(_v1254, _v1546);
    bkr_i64 _v424 = _v901(_v1546);
    bkr_str _v1899 = _v1653(_v1254, _v424);
    _v1599(_v1254, "int main(int argc, char** argv) {");
    _v1599(_v1254, "    bkr_init_args(argc, argv);");
    _v1599(_v1254, bkr_str_concat(bkr_str_concat("    return (int)", _v1899), "();"));
    _v1599(_v1254, "}");
    bkr_i64 _v1552 = _v1570(_v1254);
    return join_lines(_v1552);
}

bkr_str _v1901(bkr_str _v1656) {
    bkr_str _v1811 = from_char_code(34);
    bkr_str _v1855 = from_char_code(92);
    bkr_str _v1856 = "";
    bkr_i64 _v1172 = 0;
    bkr_i64 _v1902 = bkr_len((bkr_str)(intptr_t)(_v1656));
    while ((_v1172 < _v1902)) {
        bkr_str _v1857 = char_at(_v1656, _v1172);
        bkr_i64 _v1859 = char_code(_v1857);
        if ((_v1859 == 10)) {
            _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), "n");
        } else {
            if ((_v1859 == 13)) {
                _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), "r");
            } else {
                if ((_v1859 == 9)) {
                    _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), "t");
                } else {
                    if ((_v1859 == 34)) {
                        _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), _v1811);
                    } else {
                        if ((_v1859 == 92)) {
                            _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), _v1855);
                        } else {
                            if ((((_v1859 == 47) && (_v1172 > 0)) && (char_code_at(_v1656, (_v1172 - 1)) == 42))) {
                                _v1856 = bkr_str_concat(bkr_str_concat(_v1856, _v1855), _v1857);
                            } else {
                                _v1856 = bkr_str_concat(_v1856, _v1857);
                            }
                        }
                    }
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1856;
}

bkr_str _v1903(bkr_str _v1398) {
    bkr_str _v1811 = from_char_code(34);
    return bkr_str_concat(bkr_str_concat(_v1811, _v1901(_v1398)), _v1811);
}

bkr_str _v1904(bkr_i64 _v1398) {
    return int_to_string(_v1398);
}

bkr_str _v1905(bkr_bool _v1398) {
    if (_v1398) {
        return "true";
    }
    return "false";
}

bkr_str _v1906(void) {
    return "null";
}

bkr_str _v1907(bkr_str _v1841, bkr_str _v1398) {
    bkr_str _v1811 = from_char_code(34);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1811, _v1841), _v1811), ":"), _v1903(_v1398));
}

bkr_str _v1908(bkr_str _v1841, bkr_i64 _v1398) {
    bkr_str _v1811 = from_char_code(34);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1811, _v1841), _v1811), ":"), _v1904(_v1398));
}

bkr_str _v1909(bkr_str _v1841, bkr_bool _v1398) {
    bkr_str _v1811 = from_char_code(34);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1811, _v1841), _v1811), ":"), _v1905(_v1398));
}

bkr_str _v1910(bkr_str _v1841, bkr_str _v1911) {
    bkr_str _v1811 = from_char_code(34);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1811, _v1841), _v1811), ":"), _v1911);
}

_v1912 _v1914(void) {
    bkr_i64 _v574 = vec_new();
    bkr_i64 _v1915 = vec_new();
    return (_v1912){._v1913 = _v574, ._v613 = _v1915};
}

void _v1916(_v1912 _v1917, bkr_str _v1841, bkr_str _v1398) {
    vec_push(_v1917._v1913, ((bkr_i64)(intptr_t)_v1841));
    vec_push(_v1917._v613, ((bkr_i64)(intptr_t)_v1903(_v1398)));
}

void _v1918(_v1912 _v1917, bkr_str _v1841, bkr_i64 _v1398) {
    vec_push(_v1917._v1913, ((bkr_i64)(intptr_t)_v1841));
    vec_push(_v1917._v613, ((bkr_i64)(intptr_t)_v1904(_v1398)));
}

void _v1919(_v1912 _v1917, bkr_str _v1841, bkr_bool _v1398) {
    vec_push(_v1917._v1913, ((bkr_i64)(intptr_t)_v1841));
    vec_push(_v1917._v613, ((bkr_i64)(intptr_t)_v1905(_v1398)));
}

void _v1920(_v1912 _v1917, bkr_str _v1841, bkr_str _v1911) {
    vec_push(_v1917._v1913, ((bkr_i64)(intptr_t)_v1841));
    vec_push(_v1917._v613, ((bkr_i64)(intptr_t)_v1911));
}

bkr_str _v1921(_v1912 _v1917) {
    bkr_str _v1811 = from_char_code(34);
    bkr_str _v1856 = "{";
    bkr_i64 _v399 = vec_len(_v1917._v1913);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v399)) {
        if ((_v1172 > 0)) {
            _v1856 = bkr_str_concat(_v1856, ",");
        }
        bkr_str _v574 = (bkr_str)(intptr_t)(vec_get(_v1917._v1913, _v1172));
        bkr_str _v1915 = (bkr_str)(intptr_t)(vec_get(_v1917._v613, _v1172));
        _v1856 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1856, _v1811), _v574), _v1811), ":"), _v1915);
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1856, "}");
}

_v1922 _v1923(void) {
    bkr_i64 _v1924 = vec_new();
    return (_v1922){._v423 = _v1924};
}

void _v1925(_v1922 _v1926, bkr_str _v1398) {
    vec_push(_v1926._v423, ((bkr_i64)(intptr_t)_v1903(_v1398)));
}

void _v1927(_v1922 _v1926, bkr_i64 _v1398) {
    vec_push(_v1926._v423, ((bkr_i64)(intptr_t)_v1904(_v1398)));
}

void _v1928(_v1922 _v1926, bkr_bool _v1398) {
    vec_push(_v1926._v423, ((bkr_i64)(intptr_t)_v1905(_v1398)));
}

void _v1929(_v1922 _v1926, bkr_str _v1911) {
    vec_push(_v1926._v423, ((bkr_i64)(intptr_t)_v1911));
}

bkr_str _v1930(_v1922 _v1926) {
    bkr_str _v1856 = "[";
    bkr_i64 _v399 = vec_len(_v1926._v423);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v399)) {
        if ((_v1172 > 0)) {
            _v1856 = bkr_str_concat(_v1856, ",");
        }
        bkr_str _v558 = (bkr_str)(intptr_t)(vec_get(_v1926._v423, _v1172));
        _v1856 = bkr_str_concat(_v1856, _v558);
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1856, "]");
}

bkr_i64 _v1931(bkr_str _v1932, bkr_i64 _v1933) {
    bkr_i64 _v1172 = _v1933;
    bkr_i64 _v1902 = bkr_len((bkr_str)(intptr_t)(_v1932));
    while ((_v1172 < _v1902)) {
        bkr_i64 _v1208 = char_code_at(_v1932, _v1172);
        if (((((_v1208 != 32) && (_v1208 != 9)) && (_v1208 != 10)) && (_v1208 != 13))) {
            return _v1172;
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1172;
}

bkr_str _v1934(bkr_str _v1932, bkr_str _v1841) {
    bkr_str _v1811 = from_char_code(34);
    bkr_str _v386 = bkr_str_concat(bkr_str_concat(_v1811, _v1841), _v1811);
    bkr_i64 _v1935 = bkr_str_index_of((bkr_str)(intptr_t)(_v1932), (bkr_str)(intptr_t)(_v386));
    if ((_v1935 < 0)) {
        return "";
    }
    bkr_i64 _v1937 = (_v1935 + bkr_len((bkr_str)(intptr_t)(_v386)));
    bkr_i64 _v1938 = bkr_str_index_of((bkr_str)(intptr_t)(substring(_v1932, _v1937, bkr_len((bkr_str)(intptr_t)(_v1932)))), (bkr_str)(intptr_t)(":"));
    if ((_v1938 < 0)) {
        return "";
    }
    bkr_i64 _v1939 = _v1931(_v1932, ((_v1937 + _v1938) + 1));
    if ((_v1939 >= bkr_len((bkr_str)(intptr_t)(_v1932)))) {
        return "";
    }
    bkr_i64 _v1455 = char_code_at(_v1932, _v1939);
    if ((_v1455 == 34)) {
        bkr_i64 _v1645 = (_v1939 + 1);
        while ((_v1645 < bkr_len((bkr_str)(intptr_t)(_v1932)))) {
            bkr_i64 _v1857 = char_code_at(_v1932, _v1645);
            if (((_v1857 == 34) && (char_code_at(_v1932, (_v1645 - 1)) != 92))) {
                return substring(_v1932, (_v1939 + 1), _v1645);
            }
            _v1645 = (_v1645 + 1);
        }
        return "";
    }
    if ((_v1455 == 123)) {
        bkr_i64 _v1365 = 1;
        bkr_i64 _v1645 = (_v1939 + 1);
        while (((_v1645 < bkr_len((bkr_str)(intptr_t)(_v1932))) && (_v1365 > 0))) {
            bkr_i64 _v1857 = char_code_at(_v1932, _v1645);
            if ((_v1857 == 123)) {
                _v1365 = (_v1365 + 1);
            } else {
                if ((_v1857 == 125)) {
                    _v1365 = (_v1365 - 1);
                }
            }
            _v1645 = (_v1645 + 1);
        }
        return substring(_v1932, _v1939, _v1645);
    }
    if ((_v1455 == 91)) {
        bkr_i64 _v1365 = 1;
        bkr_i64 _v1645 = (_v1939 + 1);
        while (((_v1645 < bkr_len((bkr_str)(intptr_t)(_v1932))) && (_v1365 > 0))) {
            bkr_i64 _v1857 = char_code_at(_v1932, _v1645);
            if ((_v1857 == 91)) {
                _v1365 = (_v1365 + 1);
            } else {
                if ((_v1857 == 93)) {
                    _v1365 = (_v1365 - 1);
                }
            }
            _v1645 = (_v1645 + 1);
        }
        return substring(_v1932, _v1939, _v1645);
    }
    bkr_i64 _v574 = _v1939;
    while ((_v574 < bkr_len((bkr_str)(intptr_t)(_v1932)))) {
        bkr_i64 _v1857 = char_code_at(_v1932, _v574);
        if ((((((((_v1857 == 44) || (_v1857 == 125)) || (_v1857 == 93)) || (_v1857 == 32)) || (_v1857 == 10)) || (_v1857 == 13)) || (_v1857 == 9))) {
            return substring(_v1932, _v1939, _v574);
        }
        _v574 = (_v574 + 1);
    }
    return substring(_v1932, _v1939, bkr_len((bkr_str)(intptr_t)(_v1932)));
}

bkr_str _v1940(bkr_str _v1932, bkr_str _v1841) {
    return _v1934(_v1932, _v1841);
}

bkr_i64 _v1941(bkr_str _v1932, bkr_str _v1841) {
    bkr_str _v1656 = _v1934(_v1932, _v1841);
    if ((bkr_len((bkr_str)(intptr_t)(_v1656)) == 0)) {
        return 0;
    }
    return parse_int(_v1656);
}

bkr_bool _v1942(bkr_str _v1932, bkr_str _v1841) {
    bkr_str _v1656 = _v1934(_v1932, _v1841);
    return bkr_str_eq(_v1656, "true");
}

bkr_bool _v1943(bkr_str _v1932, bkr_str _v1841) {
    bkr_str _v1811 = from_char_code(34);
    bkr_str _v386 = bkr_str_concat(bkr_str_concat(_v1811, _v1841), _v1811);
    return (bkr_str_index_of((bkr_str)(intptr_t)(_v1932), (bkr_str)(intptr_t)(_v386)) >= 0);
}

bkr_i64 _v1944(bkr_str _v1945) {
    bkr_i64 _v396 = vec_new();
    bkr_i64 _v1902 = bkr_len((bkr_str)(intptr_t)(_v1945));
    if ((_v1902 < 2)) {
        return _v396;
    }
    bkr_i64 _v1172 = 0;
    while (((_v1172 < _v1902) && (char_code_at(_v1945, _v1172) != 91))) {
        _v1172 = (_v1172 + 1);
    }
    _v1172 = (_v1172 + 1);
    while ((_v1172 < _v1902)) {
        _v1172 = _v1931(_v1945, _v1172);
        if (((_v1172 >= _v1902) || (char_code_at(_v1945, _v1172) == 93))) {
            break;
        }
        bkr_i64 _v339 = _v1172;
        bkr_i64 _v1455 = char_code_at(_v1945, _v1172);
        if ((_v1455 == 34)) {
            _v1172 = (_v1172 + 1);
            while ((_v1172 < _v1902)) {
                bkr_i64 _v1857 = char_code_at(_v1945, _v1172);
                if (((_v1857 == 34) && (char_code_at(_v1945, (_v1172 - 1)) != 92))) {
                    bkr_str _v1946 = substring(_v1945, (_v339 + 1), _v1172);
                    vec_push(_v396, ((bkr_i64)(intptr_t)_v1946));
                    _v1172 = (_v1172 + 1);
                    break;
                }
                _v1172 = (_v1172 + 1);
            }
        } else {
            if ((_v1455 == 123)) {
                bkr_i64 _v1365 = 1;
                _v1172 = (_v1172 + 1);
                while (((_v1172 < _v1902) && (_v1365 > 0))) {
                    bkr_i64 _v1857 = char_code_at(_v1945, _v1172);
                    if ((_v1857 == 123)) {
                        _v1365 = (_v1365 + 1);
                    } else {
                        if ((_v1857 == 125)) {
                            _v1365 = (_v1365 - 1);
                        }
                    }
                    _v1172 = (_v1172 + 1);
                }
                vec_push(_v396, ((bkr_i64)(intptr_t)substring(_v1945, _v339, _v1172)));
            } else {
                while ((_v1172 < _v1902)) {
                    bkr_i64 _v1857 = char_code_at(_v1945, _v1172);
                    if (((_v1857 == 44) || (_v1857 == 93))) {
                        break;
                    }
                    _v1172 = (_v1172 + 1);
                }
                vec_push(_v396, ((bkr_i64)(intptr_t)substring(_v1945, _v339, _v1172)));
            }
        }
        _v1172 = _v1931(_v1945, _v1172);
        if (((_v1172 < _v1902) && (char_code_at(_v1945, _v1172) == 44))) {
            _v1172 = (_v1172 + 1);
        }
    }
    return _v396;
}

bkr_bool _v1947(_v341 _v1546) {
    return (vec_len(_v904(_v1546)) <= _v273);
}

bkr_str _v1948(bkr_str _v1656) {
    return _v1903(_v1656);
}

bkr_str _v1949(bkr_str _v319, bkr_i64 _v1950, bkr_i64 _v1951, bkr_str _v1952, bkr_str _v1953, bkr_str _v1954) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("kind", _v319)), _v1955), _v1908("source_start", _v1950)), _v1955), _v1908("source_end", _v1951)), _v1955), _v1907("replacement", _v1952)), _v1955), _v1907("applicability", _v1953)), _v1955), _v1907("confidence", _v1954)), "}");
}

bkr_str _v1956(void) {
    return "[]";
}

bkr_str _v1957(bkr_str _v1958) {
    return bkr_str_concat(bkr_str_concat("[", _v1958), "]");
}

bkr_str _v1959(bkr_i64 _v425, bkr_i64 _v1036) {
    if (((_v1036 >= 0) && (_v1036 < vec_len(_v425)))) {
        return vec_get(_v425, _v1036);
    }
    return "";
}

bkr_i64 _v1960(void) {
    bkr_i64 _v1254 = vec_new();
    return _v1254;
}

bkr_str _v1961(bkr_i64 _v1254) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v1254))) {
        if ((_v1172 > 0)) {
            _v1196 = bkr_str_concat(_v1196, ",");
        }
        bkr_str _v1962 = (bkr_str)(intptr_t)(vec_get(_v1254, _v1172));
        _v1196 = bkr_str_concat(_v1196, _v1962);
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_i64 _v1963(bkr_i64 _v1254) {
    return vec_len(_v1254);
}

bkr_i64 _v1964(bkr_i64 _v1254, bkr_str _v1962) {
    vec_push(_v1254, ((bkr_i64)(intptr_t)_v1962));
    return _v1254;
}

bkr_bool _v1965(bkr_i64 _v613, bkr_i64 _v387) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v613))) {
        if ((vec_get(_v613, _v1172) == _v387)) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v1966(void) {
    bkr_i64 _v613 = vec_new();
    return _v613;
}

bkr_i64 _v1967(bkr_i64 _v613) {
    bkr_i64 _v1196 = vec_new();
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v613))) {
        bkr_i64 _v1968 = vec_get(_v613, _v1172);
        vec_push(_v1196, _v1968);
        _v1172 = (_v1172 + 1);
    }
    return _v1196;
}

bkr_i64 _v1969(bkr_i64 _v613, bkr_i64 _v387) {
    bkr_i64 _v1196 = _v1967(_v613);
    vec_push(_v1196, _v387);
    return _v1196;
}

bkr_i64 _v1970(bkr_str _v1212) {
    bkr_i64 _v399 = 1;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < bkr_len((bkr_str)(intptr_t)(_v1212)))) {
        if ((char_code_at(_v1212, _v1172) == 10)) {
            _v399 = (_v399 + 1);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v399;
}

bkr_i64 _v1971(bkr_i64 _v558) {
    return _v1972(_v560(_v558));
}

bkr_i64 _v1972(_v428 _v563) {
    bkr_i64 _v319 = _v569(_v563);
    if ((_v319 == _v224)) {
        return _v869(_v563);
    }
    if ((_v319 == _v249)) {
        return _v879(_v563);
    }
    if ((_v319 == _v254)) {
        return _v887(_v563);
    }
    if ((_v319 == _v259)) {
        return _v1168(_v563);
    }
    if ((_v319 == _v260)) {
        return _v1180(_v563);
    }
    return (-1);
}

bkr_i64 _v1973(bkr_i64 _v558) {
    return _v1974(_v560(_v558));
}

bkr_i64 _v1974(_v428 _v563) {
    if ((_v569(_v563) == _v224)) {
        return _v907(_v872(_v563));
    }
    return 0;
}

bkr_i64 _v1975(bkr_i64 _v558) {
    return _v1976(_v560(_v558));
}

bkr_i64 _v1976(_v428 _v563) {
    if ((_v569(_v563) == _v254)) {
        return _v907(_v890(_v563));
    }
    return 0;
}

bkr_i64 _v1977(bkr_i64 _v558) {
    return _v1978(_v560(_v558));
}

bkr_i64 _v1978(_v428 _v563) {
    if ((_v569(_v563) == _v224)) {
        return _v590(_v877(_v563));
    }
    return 0;
}

bkr_str _v1979(bkr_i64 _v425, bkr_i64 _v558) {
    return _v1980(_v425, _v560(_v558));
}

bkr_str _v1980(bkr_i64 _v425, _v428 _v563) {
    _v341 _v1981 = _v588(_v563);
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("kind", _v318(_v569(_v563)))), _v1955), _v1907("category", _v329(_v331(_v569(_v563))))), _v1955), _v1907("name", _v1959(_v425, _v1972(_v563)))), _v1955), _v1908("source_start", _v512(_v1981))), _v1955), _v1908("source_end", _v513(_v1981))), _v1955), _v1909("span_known", ((_v512(_v1981) != _v268) && (_v513(_v1981) != _v268)))), _v1955), _v1908("param_count", _v1974(_v563))), _v1955), _v1908("field_count", _v1976(_v563))), _v1955), _v1908("statement_count", _v1978(_v563))), "}");
}

bkr_i64 _v1982(bkr_i64 _v423, bkr_i64 _v319) {
    return _v1983(_v605(_v423), _v319);
}

bkr_i64 _v1983(_v434 _v1186, bkr_i64 _v319) {
    bkr_i64 _v399 = 0;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v341 _v563 = _v913(_v1186, _v1172);
        if ((_v510(_v563) == _v319)) {
            _v399 = (_v399 + 1);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v399;
}

bkr_str _v1984(bkr_i64 _v0) {
    _v341 _v1546 = _v477(_v0);
    return _v1985(_v904(_v1546), _v899(_v1546));
}

bkr_str _v1985(bkr_i64 _v425, _v434 _v1186) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        if ((_v1172 > 0)) {
            _v1196 = bkr_str_concat(_v1196, ",");
        }
        _v1196 = bkr_str_concat(_v1196, _v1980(_v425, _v914(_v1186, _v1172)));
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v1986(bkr_i64 _v425, bkr_i64 _v606) {
    return _v1987(_v425, _v605(_v606));
}

bkr_str _v1987(bkr_i64 _v425, _v434 _v608) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v608))) {
        if ((_v1172 > 0)) {
            _v1196 = bkr_str_concat(_v1196, ",");
        }
        _v1196 = bkr_str_concat(_v1196, _v1988(_v425, _v913(_v608, _v1172)));
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v1989(bkr_i64 _v425, bkr_i64 _v1990) {
    if (_v524(_v1990)) {
        return "null";
    }
    return _v1988(_v425, _v514(_v1990));
}

bkr_str _v1991(bkr_i64 _v425, bkr_i64 _v578) {
    return _v1992(_v425, _v580(_v578));
}

bkr_str _v1992(bkr_i64 _v425, _v429 _v583) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        if ((_v1172 > 0)) {
            _v1196 = bkr_str_concat(_v1196, ",");
        }
        _v1196 = bkr_str_concat(_v1196, _v1988(_v425, _v587(_v1111(_v583, _v1172))));
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v1993(bkr_i64 _v425, bkr_i64 _v463) {
    return _v1994(_v425, _v593(_v463));
}

bkr_str _v1994(bkr_i64 _v425, _v433 _v473) {
    bkr_str _v1955 = ",";
    bkr_i64 _v319 = _v597(_v473);
    bkr_i64 _v387 = _v598(_v473);
    bkr_str _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("kind", _v328(_v319))), _v1955), _v1908("source_start", _v602(_v473))), _v1955), _v1908("source_end", _v603(_v473))), _v1955), _v1909("span_known", ((_v602(_v473) != _v268) && (_v603(_v473) != _v268))));
    if ((_v319 == _v283)) {
        _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1908("value", _v387));
    } else {
        if ((_v319 == _v284)) {
            _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1909("value", (_v387 == 1)));
        } else {
            if (((((((_v319 == _v285) || (_v319 == _v287)) || (_v319 == _v290)) || (_v319 == _v291)) || (_v319 == _v292)) || (_v319 == _v293))) {
                _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("binding", _v1959(_v425, _v387)));
            }
        }
    }
    return bkr_str_concat(_v1196, "}");
}

bkr_str _v1995(bkr_i64 _v425, bkr_i64 _v406, bkr_i64 _v407) {
    return _v1996(_v425, _v619(_v406), _v605(_v407));
}

bkr_str _v1996(bkr_i64 _v425, _v436 _v621, _v434 _v976) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        if ((_v1172 > 0)) {
            _v1196 = bkr_str_concat(_v1196, ",");
        }
        _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, "{"), _v1910("pattern", _v1994(_v425, _v925(_v621, _v1172)))), ","), _v1910("body", _v1988(_v425, _v913(_v976, _v1172)))), "}");
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v1997(bkr_i64 _v425, bkr_i64 _v447) {
    return _v1998(_v425, _v539(_v447));
}

bkr_str _v1998(bkr_i64 _v425, _v426 _v542) {
    _v435 _v1008 = _v728(_v542);
    _v434 _v1009 = _v731(_v542);
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v916(_v1008))) {
        if ((_v1172 > 0)) {
            _v1196 = bkr_str_concat(_v1196, ",");
        }
        _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, "{"), _v1907("name", _v1959(_v425, _v918(_v1008, _v1172)))), ","), _v1910("value", _v1988(_v425, _v913(_v1009, _v1172)))), "}");
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v1999(bkr_i64 _v425, bkr_i64 _v2000) {
    _v426 _v542 = _v538(_v2000);
    return _v1988(_v425, _v547(_v542));
}

bkr_str _v2001(bkr_i64 _v425, bkr_i64 _v1615) {
    _v427 _v554 = _v550(_v1615);
    return _v1988(_v425, _v587(_v554));
}

bkr_str _v2002(bkr_i64 _v425, bkr_i64 _v447) {
    return _v1988(_v425, _v477(_v447));
}

bkr_str _v1988(bkr_i64 _v425, _v341 _v452) {
    bkr_str _v1955 = ",";
    bkr_i64 _v319 = _v510(_v452);
    bkr_str _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("kind", _v318(_v319))), _v1955), _v1907("category", _v329(_v511(_v452)))), _v1955), _v1908("source_start", _v512(_v452))), _v1955), _v1908("source_end", _v513(_v452))), _v1955), _v1909("span_known", ((_v512(_v452) != _v268) && (_v513(_v452) != _v268))));
    if ((_v319 == _v223)) {
        _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v664(_v452)))), _v1955), _v1907("entry", _v1959(_v425, _v901(_v452)))), _v1955), _v1910("items", _v1987(_v425, _v899(_v452))));
    } else {
        if ((_v319 == _v224)) {
            _v428 _v563 = _v561(_v452);
            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v869(_v563)))), _v1955), _v1910("params", _v1987(_v425, _v872(_v563)))), _v1955), _v1910("return_type", _v1989(_v425, _v875(_v563)))), _v1955), _v1910("body", _v1988(_v425, _v589(_v877(_v563)))));
        } else {
            if ((_v319 == _v225)) {
                _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v863(_v452)))), _v1955), _v1910("type", _v1988(_v425, _v586(_v867(_v452)))));
            } else {
                if ((_v319 == _v226)) {
                    _v346 _v521 = _v519(_v452);
                    bkr_i64 _v2003 = _v530(_v521);
                    _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("type_kind", _v327(_v2003))), _v1955), _v1908("type_tag", _v2003));
                    if ((_v2003 == _v309)) {
                        _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("struct_name", _v1959(_v425, _v532(_v521))));
                    } else {
                        if ((_v2003 == _v308)) {
                            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("element_type_kind", _v327(_v533(_v521)))), _v1955), _v1908("array_len", _v534(_v521)));
                        } else {
                            if ((_v2003 == _v310)) {
                                bkr_i64 _v954 = _v535(_v521);
                                bkr_i64 _v1376 = _v536(_v521);
                                _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("element_type_kind", _v327(_v954)));
                                if (((_v954 == _v309) && (_v1376 >= 0))) {
                                    _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("element_struct_name", _v1959(_v425, _v1376)));
                                }
                            } else {
                                if ((_v2003 == _v311)) {
                                    bkr_i64 _v1378 = _v535(_v521);
                                    bkr_i64 _v1380 = _v536(_v521);
                                    _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("key_type_kind", _v327(_v1378))), _v1955), _v1907("value_type_kind", _v327(_v1380)));
                                } else {
                                    if ((_v2003 == _v312)) {
                                        bkr_i64 _v1382 = _v535(_v521);
                                        bkr_i64 _v1383 = _v536(_v521);
                                        _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("inner_type_kind", _v327(_v1382)));
                                        if (((_v1382 == _v309) && (_v1383 >= 0))) {
                                            _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("inner_struct_name", _v1959(_v425, _v1383)));
                                        }
                                    } else {
                                        if ((_v2003 == _v313)) {
                                            bkr_i64 _v1385 = _v535(_v521);
                                            bkr_i64 _v1387 = _v536(_v521);
                                            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("ok_type_kind", _v327(_v1385))), _v1955), _v1907("err_type_kind", _v327(_v1387)));
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if ((_v319 == _v227)) {
                        _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("statements", _v1992(_v425, _v581(_v452))));
                    } else {
                        if ((_v319 == _v228)) {
                            _v427 _v554 = _v552(_v452);
                            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v758(_v554)))), _v1955), _v1910("declared_type", _v1989(_v425, _v761(_v554)))), _v1955), _v1910("init", _v1989(_v425, _v764(_v554))));
                        } else {
                            if ((_v319 == _v229)) {
                                _v427 _v554 = _v552(_v452);
                                _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("expr", _v1989(_v425, _v769(_v554))));
                            } else {
                                if ((_v319 == _v230)) {
                                    _v427 _v554 = _v552(_v452);
                                    _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("condition", _v1999(_v425, _v828(_v554)))), _v1955), _v1910("then", _v1988(_v425, _v589(_v830(_v554))))), _v1955), _v1910("else", _v1989(_v425, _v833(_v554))));
                                } else {
                                    if ((_v319 == _v231)) {
                                        _v427 _v554 = _v552(_v452);
                                        _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("condition", _v1999(_v425, _v850(_v554)))), _v1955), _v1910("body", _v1988(_v425, _v589(_v852(_v554)))));
                                    } else {
                                        if ((_v319 == _v232)) {
                                            _v427 _v554 = _v552(_v452);
                                            _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("expr", _v1999(_v425, _v861(_v554))));
                                        } else {
                                            if ((_v319 == _v233)) {
                                                _v427 _v554 = _v552(_v452);
                                                _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("target", _v1999(_v425, _v855(_v554)))), _v1955), _v1910("value", _v1999(_v425, _v858(_v554))));
                                            } else {
                                                if ((_v319 == _v236)) {
                                                    _v427 _v554 = _v552(_v452);
                                                    _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("binding", _v1959(_v425, _v835(_v554)))), _v1955), _v1910("start", _v1999(_v425, _v838(_v554)))), _v1955), _v1910("end", _v1999(_v425, _v841(_v554)))), _v1955), _v1909("inclusive", (_v843(_v554) == 1))), _v1955), _v1910("body", _v1988(_v425, _v589(_v845(_v554)))));
                                                } else {
                                                    if ((_v319 == _v237)) {
                                                        _v427 _v554 = _v552(_v452);
                                                        _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("body", _v1988(_v425, _v589(_v847(_v554)))));
                                                    } else {
                                                        if ((_v319 == _v238)) {
                                                            _v427 _v554 = _v552(_v452);
                                                            _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("stmt", _v2001(_v425, _v773(_v554))));
                                                        } else {
                                                            if ((_v319 == _v242)) {
                                                                _v426 _v542 = _v540(_v452);
                                                                _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("op", _v1321(_v672(_v542)))), _v1955), _v1910("left", _v1999(_v425, _v675(_v542)))), _v1955), _v1910("right", _v1999(_v425, _v678(_v542))));
                                                            } else {
                                                                if ((_v319 == _v240)) {
                                                                    _v426 _v542 = _v540(_v452);
                                                                    _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("expr", _v1999(_v425, _v778(_v542))));
                                                                } else {
                                                                    if ((_v319 == _v243)) {
                                                                        _v426 _v542 = _v540(_v452);
                                                                        _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("op", _v1321(_v682(_v542)))), _v1955), _v1910("operand", _v1999(_v425, _v685(_v542))));
                                                                    } else {
                                                                        if ((_v319 == _v261)) {
                                                                            _v426 _v542 = _v540(_v452);
                                                                            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("receiver", _v1999(_v425, _v694(_v542)))), _v1955), _v1907("method", _v1959(_v425, _v697(_v542)))), _v1955), _v1910("args", _v1987(_v425, _v699(_v542))));
                                                                        } else {
                                                                            if ((_v319 == _v244)) {
                                                                                _v426 _v542 = _v540(_v452);
                                                                                _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("callee", _v1959(_v425, _v689(_v542)))), _v1955), _v1910("args", _v1987(_v425, _v692(_v542))));
                                                                            } else {
                                                                                if ((_v319 == _v245)) {
                                                                                    _v426 _v542 = _v540(_v452);
                                                                                    _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v663(_v542))));
                                                                                } else {
                                                                                    if ((_v319 == _v246)) {
                                                                                        _v426 _v542 = _v540(_v452);
                                                                                        _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1908("value", _v666(_v542)));
                                                                                    } else {
                                                                                        if ((_v319 == _v247)) {
                                                                                            _v426 _v542 = _v540(_v452);
                                                                                            _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1909("value", (_v666(_v542) == 1)));
                                                                                        } else {
                                                                                            if ((_v319 == _v248)) {
                                                                                                _v426 _v542 = _v540(_v452);
                                                                                                _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("value", ((bkr_str)(_v666(_v542)))));
                                                                                            } else {
                                                                                                if ((_v319 == _v249)) {
                                                                                                    _v428 _v563 = _v561(_v452);
                                                                                                    _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v879(_v563)))), _v1955), _v1910("type", _v1989(_v425, _v882(_v563)))), _v1955), _v1910("value", _v1989(_v425, _v885(_v563))));
                                                                                                } else {
                                                                                                    if ((_v319 == _v260)) {
                                                                                                        _v428 _v563 = _v561(_v452);
                                                                                                        _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v1180(_v563)))), _v1955), _v1910("target", _v1989(_v425, _v1181(_v563))));
                                                                                                    } else {
                                                                                                        if ((_v319 == _v250)) {
                                                                                                            _v426 _v542 = _v540(_v452);
                                                                                                            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("condition", _v1999(_v425, _v734(_v542)))), _v1955), _v1910("then", _v1999(_v425, _v737(_v542)))), _v1955), _v1910("else", _v1999(_v425, _v740(_v542))));
                                                                                                        } else {
                                                                                                            if ((_v319 == _v251)) {
                                                                                                                _v426 _v542 = _v540(_v452);
                                                                                                                _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("value", ((bkr_str)(_v666(_v542)))));
                                                                                                            } else {
                                                                                                                if ((_v319 == _v252)) {
                                                                                                                    _v426 _v542 = _v540(_v452);
                                                                                                                    _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("elements", _v1987(_v425, _v702(_v542))));
                                                                                                                } else {
                                                                                                                    if ((_v319 == _v239)) {
                                                                                                                        _v426 _v542 = _v540(_v452);
                                                                                                                        _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("element", _v1999(_v425, _v704(_v542)))), _v1955), _v1908("count", _v707(_v542)));
                                                                                                                    } else {
                                                                                                                        if ((_v319 == _v253)) {
                                                                                                                            _v426 _v542 = _v540(_v452);
                                                                                                                            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("base", _v1999(_v425, _v712(_v542)))), _v1955), _v1910("index", _v1999(_v425, _v715(_v542))));
                                                                                                                        } else {
                                                                                                                            if ((_v319 == _v254)) {
                                                                                                                                _v428 _v563 = _v561(_v452);
                                                                                                                                _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v887(_v563)))), _v1955), _v1910("fields", _v1987(_v425, _v890(_v563))));
                                                                                                                            } else {
                                                                                                                                if ((_v319 == _v259)) {
                                                                                                                                    _v428 _v563 = _v561(_v452);
                                                                                                                                    _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v1168(_v563)))), _v1955), _v1908("variant_count", _v916(_v1169(_v563)))), _v1955), _v1908("payload_count", _v1171(_v563))), _v1955), _v1908("payload_arity_sum", _v1173(_v563)));
                                                                                                                                } else {
                                                                                                                                    if ((_v319 == _v255)) {
                                                                                                                                        _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v892(_v452)))), _v1955), _v1910("type", _v1989(_v425, _v895(_v452))));
                                                                                                                                    } else {
                                                                                                                                        if ((_v319 == _v256)) {
                                                                                                                                            _v426 _v542 = _v540(_v452);
                                                                                                                                            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("base", _v1999(_v425, _v720(_v542)))), _v1955), _v1907("field", _v1959(_v425, _v723(_v542))));
                                                                                                                                        } else {
                                                                                                                                            if ((_v319 == _v257)) {
                                                                                                                                                _v426 _v542 = _v540(_v452);
                                                                                                                                                _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("name", _v1959(_v425, _v725(_v542)))), _v1955), _v1910("fields", _v1998(_v425, _v542)));
                                                                                                                                            } else {
                                                                                                                                                if ((_v319 == _v258)) {
                                                                                                                                                    _v426 _v542 = _v540(_v452);
                                                                                                                                                    _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1910("scrutinee", _v1999(_v425, _v743(_v542)))), _v1955), _v1910("arms", _v1996(_v425, _v746(_v542), _v749(_v542))));
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1196, "}");
}

bkr_str _v2004(bkr_str _v1212, bkr_i64 _v0) {
    bkr_str _v1955 = ",";
    _v341 _v1546 = _v477(_v0);
    bkr_i64 _v425 = _v904(_v1546);
    _v434 _v1186 = _v899(_v1546);
    bkr_str _v2005 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("kind", _v318(_v510(_v1546)))), _v1955), _v1907("name", _v1959(_v425, _v664(_v1546)))), _v1955), _v1907("entry", _v1959(_v425, _v901(_v1546)))), _v1955), _v1908("source_start", _v512(_v1546))), _v1955), _v1908("source_end", _v513(_v1546))), _v1955), _v1909("span_known", ((_v512(_v1546) != _v268) && (_v513(_v1546) != _v268)))), "}");
    bkr_str _v2006 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1908("source_bytes", bkr_len((bkr_str)(intptr_t)(_v1212)))), _v1955), _v1908("source_lines", _v1970(_v1212))), _v1955), _v1908("item_count", _v907(_v1186))), _v1955), _v1908("function_count", _v1983(_v1186, _v224))), _v1955), _v1908("struct_count", _v1983(_v1186, _v254))), _v1955), _v1908("enum_count", _v1983(_v1186, _v259))), _v1955), _v1908("const_count", _v1983(_v1186, _v249))), "}");
    bkr_bool _v2007 = _v1947(_v1546);
    bkr_str _v2008 = "[]";
    bkr_str _v2009 = bkr_str_concat(bkr_str_concat("{", _v1907("kind", "kernel")), "}");
    if (_v2007) {
        _v2008 = _v1985(_v425, _v1186);
        _v2009 = _v1988(_v425, _v477(_v0));
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.self_host.ast.v1")), _v1955), _v1907("representation", "bootstrap_vec_i64")), _v1955), _v1909("source_byte_spans", BKR_TRUE)), _v1955), _v1909("complete_tree", _v2007)), _v1955), _v1909("truncated", (!_v2007))), _v1955), _v1910("root", _v2005)), _v1955), _v1910("summary", _v2006)), _v1955), _v1910("items", _v2008)), _v1955), _v1910("tree", _v2009)), "}");
}

bkr_str _v2010(bkr_str _v1212, bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_AST_JSON: ", _v2004(_v1212, _v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v2011(bkr_str _v1196, bkr_str _v558) {
    if ((bkr_len((bkr_str)(intptr_t)(_v1196)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1196, ","), _v558);
    }
    return bkr_str_concat(_v1196, _v558);
}

bkr_str _v2012(bkr_str _v1196, bkr_str _v423) {
    if ((bkr_len((bkr_str)(intptr_t)(_v423)) <= 2)) {
        return _v1196;
    }
    bkr_str _v2013 = substring(_v423, 1, (bkr_len((bkr_str)(intptr_t)(_v423)) - 1));
    if ((bkr_len((bkr_str)(intptr_t)(_v1196)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1196, ","), _v2013);
    }
    return bkr_str_concat(_v1196, _v2013);
}

bkr_str _v2014(bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v1950, bkr_i64 _v1951) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("kind", _v319)), _v1955), _v1907("name", _v1363)), _v1955), _v1907("scope", _v2015)), _v1955), _v1908("source_start", _v1950)), _v1955), _v1908("source_end", _v1951)), _v1955), _v1909("span_known", ((_v1950 != _v268) && (_v1951 != _v268)))), "}");
}

bkr_str _v2016(bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v341 _v452) {
    return _v2014(_v319, _v1363, _v2015, _v512(_v452), _v513(_v452));
}

bkr_str _v2017(bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447) {
    return _v2016(_v319, _v1363, _v2015, _v477(_v447));
}

bkr_str _v2018(bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v433 _v473) {
    return _v2014(_v319, _v1363, _v2015, _v602(_v473), _v603(_v473));
}

bkr_str _v2019(bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v463) {
    return _v2018(_v319, _v1363, _v2015, _v593(_v463));
}

bkr_str _v2020(bkr_i64 _v425, bkr_i64 _v516, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    if (_v526(_v516)) {
        _v1196 = _v2012(_v1196, _v2021(_v425, _v517(_v516), _v2015));
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2021(bkr_i64 _v425, _v346 _v521, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    if ((_v530(_v521) == _v309)) {
        _v1196 = _v2011(_v1196, _v2016("type_reference", _v1959(_v425, _v532(_v521)), _v2015, _v586(_v521)));
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2022(bkr_i64 _v425, bkr_i64 _v463, bkr_str _v2015) {
    return _v2023(_v425, _v593(_v463), _v2015);
}

bkr_str _v2023(bkr_i64 _v425, _v433 _v473, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    bkr_i64 _v319 = _v597(_v473);
    if (((((_v319 == _v285) || (_v319 == _v287)) || (_v319 == _v290)) || (_v319 == _v291))) {
        bkr_i64 _v355 = _v598(_v473);
        if ((_v355 >= 0)) {
            _v1196 = _v2011(_v1196, _v2018("pattern_binding", _v1959(_v425, _v355), _v2015, _v473));
        }
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            _v433 _v1408 = _v592(_v345);
            _v1196 = _v2012(_v1196, _v2023(_v425, _v1408, _v2015));
        }
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            bkr_i64 _v1390 = ((bkr_i64)(_v345));
            bkr_i64 _v1172 = 0;
            while ((_v1172 < vec_len(_v1390))) {
                _v433 _v1408 = _v592(vec_get(_v1390, _v1172));
                _v1196 = _v2012(_v1196, _v2023(_v425, _v1408, _v2015));
                _v1172 = (_v1172 + 1);
            }
        } else {
            bkr_i64 _v2024 = _v600(_v473);
            bkr_i64 _v2025 = _v601(_v473);
            if ((_v2024 >= 0)) {
                _v1196 = _v2011(_v1196, _v2018("pattern_binding", _v1959(_v425, _v2024), _v2015, _v473));
            }
            if ((_v2025 >= 0)) {
                _v1196 = _v2011(_v1196, _v2018("pattern_binding", _v1959(_v425, _v2025), _v2015, _v473));
            }
        }
    }
    if ((_v319 == _v293)) {
        bkr_i64 _v2024 = _v600(_v473);
        bkr_i64 _v2025 = _v601(_v473);
        bkr_i64 _v2026 = _v599(_v473);
        if ((_v2024 >= 0)) {
            _v1196 = _v2011(_v1196, _v2018("pattern_binding", _v1959(_v425, _v2024), _v2015, _v473));
        }
        if ((_v2025 >= 0)) {
            _v1196 = _v2011(_v1196, _v2018("pattern_binding", _v1959(_v425, _v2025), _v2015, _v473));
        }
        if ((_v2026 >= 0)) {
            _v1196 = _v2011(_v1196, _v2018("pattern_binding", _v1959(_v425, _v2026), _v2015, _v473));
        }
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2027(bkr_i64 _v425, bkr_i64 _v1671, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    if (_v524(_v1671)) {
        return bkr_str_concat(_v1196, "]");
    }
    _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v1671), _v2015));
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2028(bkr_i64 _v425, _v426 _v542, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    bkr_i64 _v319 = _v545(_v542);
    if ((_v319 == _v258)) {
        _v436 _v621 = _v746(_v542);
        _v434 _v976 = _v749(_v542);
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v920(_v621))) {
            _v1196 = _v2012(_v1196, _v2023(_v425, _v925(_v621, _v1172), _v2015));
            _v341 _v1127 = _v913(_v976, _v1172);
            if ((_v510(_v1127) == _v227)) {
                _v1196 = _v2012(_v1196, _v2029(_v425, _v581(_v1127), _v2015));
            } else {
                _v1196 = _v2012(_v1196, _v2028(_v425, _v540(_v1127), _v2015));
            }
            _v1172 = (_v1172 + 1);
        }
    } else {
        if ((_v319 == _v227)) {
            _v1196 = _v2012(_v1196, _v2029(_v425, _v581(_v547(_v542)), _v2015));
        } else {
            if ((_v319 == _v242)) {
                _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v675(_v542)), _v2015));
                _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v678(_v542)), _v2015));
            } else {
                if ((_v319 == _v240)) {
                    _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v778(_v542)), _v2015));
                } else {
                    if ((_v319 == _v243)) {
                        _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v685(_v542)), _v2015));
                    } else {
                        if ((_v319 == _v261)) {
                            _v1196 = _v2012(_v1196, _v2028(_v425, _v695(_v542), _v2015));
                            _v434 _v1016 = _v699(_v542);
                            bkr_i64 _v1172 = 0;
                            while ((_v1172 < _v907(_v1016))) {
                                _v341 _v1440 = _v913(_v1016, _v1172);
                                _v1196 = _v2012(_v1196, _v2028(_v425, _v540(_v1440), _v2015));
                                _v1172 = (_v1172 + 1);
                            }
                        } else {
                            if ((_v319 == _v244)) {
                                _v434 _v1016 = _v692(_v542);
                                bkr_i64 _v1172 = 0;
                                while ((_v1172 < _v907(_v1016))) {
                                    _v341 _v1440 = _v913(_v1016, _v1172);
                                    _v1196 = _v2012(_v1196, _v2028(_v425, _v540(_v1440), _v2015));
                                    _v1172 = (_v1172 + 1);
                                }
                            } else {
                                if ((_v319 == _v250)) {
                                    _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v734(_v542)), _v2015));
                                    _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v737(_v542)), _v2015));
                                    _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v740(_v542)), _v2015));
                                } else {
                                    if ((_v319 == _v239)) {
                                        _v1196 = _v2012(_v1196, _v2027(_v425, _v704(_v542), _v2015));
                                    } else {
                                        if ((_v319 == _v252)) {
                                            _v434 _v995 = _v702(_v542);
                                            bkr_i64 _v1172 = 0;
                                            while ((_v1172 < _v907(_v995))) {
                                                _v341 _v2030 = _v913(_v995, _v1172);
                                                _v1196 = _v2012(_v1196, _v2028(_v425, _v540(_v2030), _v2015));
                                                _v1172 = (_v1172 + 1);
                                            }
                                        } else {
                                            if ((_v319 == _v253)) {
                                                _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v712(_v542)), _v2015));
                                                _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v715(_v542)), _v2015));
                                            } else {
                                                if ((_v319 == _v256)) {
                                                    _v1196 = _v2012(_v1196, _v2028(_v425, _v538(_v720(_v542)), _v2015));
                                                } else {
                                                    if ((_v319 == _v257)) {
                                                        _v434 _v1009 = _v731(_v542);
                                                        bkr_i64 _v1172 = 0;
                                                        while ((_v1172 < _v907(_v1009))) {
                                                            _v341 _v1437 = _v913(_v1009, _v1172);
                                                            _v1196 = _v2012(_v1196, _v2028(_v425, _v540(_v1437), _v2015));
                                                            _v1172 = (_v1172 + 1);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2031(bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2015) {
    return _v2032(_v425, _v551(_v370), _v2015);
}

bkr_str _v2032(bkr_i64 _v425, _v427 _v554, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    bkr_i64 _v319 = _v556(_v554);
    if ((_v319 == _v228)) {
        _v1196 = _v2011(_v1196, _v2016("local", _v1959(_v425, _v758(_v554)), _v2015, _v587(_v554)));
        _v1196 = _v2012(_v1196, _v2027(_v425, _v764(_v554), _v2015));
    } else {
        if ((_v319 == _v229)) {
            _v1196 = _v2012(_v1196, _v2027(_v425, _v769(_v554), _v2015));
        } else {
            if ((_v319 == _v230)) {
                _v1196 = _v2012(_v1196, _v2027(_v425, _v828(_v554), _v2015));
                _v1196 = _v2012(_v1196, _v2029(_v425, _v830(_v554), _v2015));
                bkr_i64 _v377 = _v833(_v554);
                if (_v526(_v377)) {
                    _v1196 = _v2012(_v1196, _v2029(_v425, _v579(_v377), _v2015));
                }
            } else {
                if ((_v319 == _v231)) {
                    _v1196 = _v2012(_v1196, _v2027(_v425, _v850(_v554), _v2015));
                    _v1196 = _v2012(_v1196, _v2029(_v425, _v852(_v554), _v2015));
                } else {
                    if ((_v319 == _v236)) {
                        _v1196 = _v2011(_v1196, _v2016("for_binding", _v1959(_v425, _v835(_v554)), _v2015, _v587(_v554)));
                        _v1196 = _v2012(_v1196, _v2027(_v425, _v838(_v554), _v2015));
                        _v1196 = _v2012(_v1196, _v2027(_v425, _v841(_v554), _v2015));
                        _v1196 = _v2012(_v1196, _v2029(_v425, _v845(_v554), _v2015));
                    } else {
                        if ((_v319 == _v237)) {
                            _v1196 = _v2012(_v1196, _v2029(_v425, _v847(_v554), _v2015));
                        } else {
                            if ((_v319 == _v233)) {
                                _v1196 = _v2012(_v1196, _v2027(_v425, _v855(_v554), _v2015));
                                _v1196 = _v2012(_v1196, _v2027(_v425, _v858(_v554), _v2015));
                            } else {
                                if ((_v319 == _v238)) {
                                    _v1196 = _v2012(_v1196, _v2032(_v425, _v550(_v773(_v554)), _v2015));
                                } else {
                                    if ((_v319 == _v232)) {
                                        _v1196 = _v2012(_v1196, _v2027(_v425, _v861(_v554), _v2015));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2033(bkr_i64 _v425, bkr_i64 _v578, bkr_str _v2015) {
    return _v2029(_v425, _v580(_v578), _v2015);
}

bkr_str _v2029(bkr_i64 _v425, _v429 _v583, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        _v1196 = _v2012(_v1196, _v2032(_v425, _v1111(_v583, _v1172), _v2015));
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2034(bkr_i64 _v0, bkr_i64 _v558, bkr_str _v2035) {
    return _v2036(_v477(_v0), _v560(_v558), _v2035);
}

bkr_str _v2036(_v341 _v1546, _v428 _v563, bkr_str _v2035) {
    bkr_i64 _v425 = _v904(_v1546);
    bkr_str _v1196 = "[";
    _v341 _v1981 = _v588(_v563);
    bkr_i64 _v319 = _v569(_v563);
    if ((_v319 == _v224)) {
        bkr_str _v2037 = _v1959(_v425, _v869(_v563));
        bkr_str _v2038 = bkr_str_concat("function:", _v2037);
        _v1196 = _v2011(_v1196, _v2016("function", _v2037, _v2035, _v1981));
        _v434 _v1145 = _v872(_v563);
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v907(_v1145))) {
            _v341 _v1523 = _v913(_v1145, _v1172);
            _v1196 = _v2011(_v1196, _v2016("parameter", _v1959(_v425, _v863(_v1523)), _v2038, _v1523));
            _v1172 = (_v1172 + 1);
        }
        _v1196 = _v2012(_v1196, _v2029(_v425, _v877(_v563), _v2038));
    } else {
        if ((_v319 == _v249)) {
            _v1196 = _v2011(_v1196, _v2016("constant", _v1959(_v425, _v879(_v563)), _v2035, _v1981));
            _v1196 = _v2012(_v1196, _v2027(_v425, _v885(_v563), _v2035));
        } else {
            if ((_v319 == _v260)) {
                _v1196 = _v2011(_v1196, _v2016("type_alias", _v1959(_v425, _v1180(_v563)), _v2035, _v1981));
            } else {
                if ((_v319 == _v254)) {
                    bkr_str _v1697 = _v1959(_v425, _v887(_v563));
                    bkr_str _v2039 = bkr_str_concat("struct:", _v1697);
                    _v1196 = _v2011(_v1196, _v2016("struct", _v1697, _v2035, _v1981));
                    _v434 _v1162 = _v890(_v563);
                    bkr_i64 _v1172 = 0;
                    while ((_v1172 < _v907(_v1162))) {
                        _v341 _v1447 = _v913(_v1162, _v1172);
                        _v1196 = _v2011(_v1196, _v2016("field", _v1959(_v425, _v892(_v1447)), _v2039, _v1447));
                        _v1172 = (_v1172 + 1);
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2040(bkr_i64 _v0) {
    return _v2041(_v477(_v0));
}

bkr_str _v2041(_v341 _v1546) {
    bkr_i64 _v425 = _v904(_v1546);
    bkr_str _v1549 = _v1959(_v425, _v664(_v1546));
    bkr_str _v2035 = bkr_str_concat("kernel:", _v1549);
    bkr_str _v1196 = "[";
    _v1196 = _v2011(_v1196, _v2016("kernel", _v1549, "global", _v1546));
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        _v1196 = _v2012(_v1196, _v2036(_v1546, _v563, _v2035));
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2042(bkr_i64 _v425, bkr_i64 _v1671, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    if (_v524(_v1671)) {
        return bkr_str_concat(_v1196, "]");
    }
    _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v1671), _v2015));
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2043(bkr_i64 _v425, _v426 _v542, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    bkr_i64 _v319 = _v545(_v542);
    if ((_v319 == _v245)) {
        _v1196 = _v2011(_v1196, _v2016("identifier", _v1959(_v425, _v663(_v542)), _v2015, _v547(_v542)));
    } else {
        if ((_v319 == _v261)) {
            _v1196 = _v2012(_v1196, _v2028(_v425, _v695(_v542), _v2015));
            _v434 _v1016 = _v699(_v542);
            bkr_i64 _v1172 = 0;
            while ((_v1172 < _v907(_v1016))) {
                _v341 _v1440 = _v913(_v1016, _v1172);
                _v1196 = _v2012(_v1196, _v2028(_v425, _v540(_v1440), _v2015));
                _v1172 = (_v1172 + 1);
            }
        } else {
            if ((_v319 == _v244)) {
                _v1196 = _v2011(_v1196, _v2016("function_call", _v1959(_v425, _v689(_v542)), _v2015, _v547(_v542)));
                _v434 _v1016 = _v692(_v542);
                bkr_i64 _v1172 = 0;
                while ((_v1172 < _v907(_v1016))) {
                    _v341 _v1440 = _v913(_v1016, _v1172);
                    _v1196 = _v2012(_v1196, _v2043(_v425, _v540(_v1440), _v2015));
                    _v1172 = (_v1172 + 1);
                }
            } else {
                if ((_v319 == _v256)) {
                    _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v720(_v542)), _v2015));
                    _v1196 = _v2011(_v1196, _v2016("field_access", _v1959(_v425, _v723(_v542)), _v2015, _v547(_v542)));
                } else {
                    if ((_v319 == _v257)) {
                        _v1196 = _v2011(_v1196, _v2016("struct_literal", _v1959(_v425, _v725(_v542)), _v2015, _v547(_v542)));
                        _v435 _v1008 = _v728(_v542);
                        _v434 _v1009 = _v731(_v542);
                        bkr_i64 _v1172 = 0;
                        while ((_v1172 < _v916(_v1008))) {
                            _v341 _v1437 = _v913(_v1009, _v1172);
                            _v1196 = _v2011(_v1196, _v2016("field_initializer", _v1959(_v425, _v918(_v1008, _v1172)), _v2015, _v547(_v542)));
                            _v1196 = _v2012(_v1196, _v2043(_v425, _v540(_v1437), _v2015));
                            _v1172 = (_v1172 + 1);
                        }
                    } else {
                        if ((_v319 == _v242)) {
                            _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v675(_v542)), _v2015));
                            _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v678(_v542)), _v2015));
                        } else {
                            if ((_v319 == _v240)) {
                                _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v778(_v542)), _v2015));
                            } else {
                                if ((_v319 == _v243)) {
                                    _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v685(_v542)), _v2015));
                                } else {
                                    if ((_v319 == _v250)) {
                                        _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v734(_v542)), _v2015));
                                        _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v737(_v542)), _v2015));
                                        _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v740(_v542)), _v2015));
                                    } else {
                                        if ((_v319 == _v239)) {
                                            _v1196 = _v2012(_v1196, _v2027(_v425, _v704(_v542), _v2015));
                                        } else {
                                            if ((_v319 == _v239)) {
                                                _v1196 = _v2012(_v1196, _v2042(_v425, _v704(_v542), _v2015));
                                            } else {
                                                if ((_v319 == _v252)) {
                                                    _v434 _v995 = _v702(_v542);
                                                    bkr_i64 _v1172 = 0;
                                                    while ((_v1172 < _v907(_v995))) {
                                                        _v341 _v2030 = _v913(_v995, _v1172);
                                                        _v1196 = _v2012(_v1196, _v2043(_v425, _v540(_v2030), _v2015));
                                                        _v1172 = (_v1172 + 1);
                                                    }
                                                } else {
                                                    if ((_v319 == _v253)) {
                                                        _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v712(_v542)), _v2015));
                                                        _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v715(_v542)), _v2015));
                                                    } else {
                                                        if ((_v319 == _v227)) {
                                                            _v1196 = _v2012(_v1196, _v2044(_v425, _v581(_v547(_v542)), _v2015));
                                                        } else {
                                                            if ((_v319 == _v258)) {
                                                                _v1196 = _v2012(_v1196, _v2043(_v425, _v538(_v743(_v542)), _v2015));
                                                                _v434 _v976 = _v749(_v542);
                                                                bkr_i64 _v1172 = 0;
                                                                while ((_v1172 < _v907(_v976))) {
                                                                    _v341 _v1127 = _v913(_v976, _v1172);
                                                                    if ((_v510(_v1127) == _v227)) {
                                                                        _v1196 = _v2012(_v1196, _v2044(_v425, _v581(_v1127), _v2015));
                                                                    } else {
                                                                        _v1196 = _v2012(_v1196, _v2043(_v425, _v540(_v1127), _v2015));
                                                                    }
                                                                    _v1172 = (_v1172 + 1);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2045(bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2015) {
    return _v2046(_v425, _v551(_v370), _v2015);
}

bkr_str _v2046(bkr_i64 _v425, _v427 _v554, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    bkr_i64 _v319 = _v556(_v554);
    if ((_v319 == _v228)) {
        _v1196 = _v2012(_v1196, _v2020(_v425, _v761(_v554), _v2015));
        _v1196 = _v2012(_v1196, _v2042(_v425, _v764(_v554), _v2015));
    } else {
        if ((_v319 == _v229)) {
            _v1196 = _v2012(_v1196, _v2042(_v425, _v769(_v554), _v2015));
        } else {
            if ((_v319 == _v230)) {
                _v1196 = _v2012(_v1196, _v2042(_v425, _v828(_v554), _v2015));
                _v1196 = _v2012(_v1196, _v2044(_v425, _v830(_v554), _v2015));
                bkr_i64 _v377 = _v833(_v554);
                if (_v526(_v377)) {
                    _v1196 = _v2012(_v1196, _v2044(_v425, _v579(_v377), _v2015));
                }
            } else {
                if ((_v319 == _v231)) {
                    _v1196 = _v2012(_v1196, _v2042(_v425, _v850(_v554), _v2015));
                    _v1196 = _v2012(_v1196, _v2044(_v425, _v852(_v554), _v2015));
                } else {
                    if ((_v319 == _v236)) {
                        _v1196 = _v2012(_v1196, _v2042(_v425, _v838(_v554), _v2015));
                        _v1196 = _v2012(_v1196, _v2042(_v425, _v841(_v554), _v2015));
                        _v1196 = _v2012(_v1196, _v2044(_v425, _v845(_v554), _v2015));
                    } else {
                        if ((_v319 == _v237)) {
                            _v1196 = _v2012(_v1196, _v2044(_v425, _v847(_v554), _v2015));
                        } else {
                            if ((_v319 == _v233)) {
                                _v1196 = _v2012(_v1196, _v2042(_v425, _v855(_v554), _v2015));
                                _v1196 = _v2012(_v1196, _v2042(_v425, _v858(_v554), _v2015));
                            } else {
                                if ((_v319 == _v238)) {
                                    _v1196 = _v2012(_v1196, _v2046(_v425, _v550(_v773(_v554)), _v2015));
                                } else {
                                    if ((_v319 == _v232)) {
                                        _v1196 = _v2012(_v1196, _v2042(_v425, _v861(_v554), _v2015));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2047(bkr_i64 _v425, bkr_i64 _v578, bkr_str _v2015) {
    return _v2044(_v425, _v580(_v578), _v2015);
}

bkr_str _v2044(bkr_i64 _v425, _v429 _v583, bkr_str _v2015) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        _v1196 = _v2012(_v1196, _v2046(_v425, _v1111(_v583, _v1172), _v2015));
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2048(bkr_i64 _v0, bkr_i64 _v558, bkr_str _v2035) {
    return _v2049(_v477(_v0), _v560(_v558), _v2035);
}

bkr_str _v2049(_v341 _v1546, _v428 _v563, bkr_str _v2035) {
    bkr_i64 _v425 = _v904(_v1546);
    bkr_str _v1196 = "[";
    bkr_i64 _v319 = _v569(_v563);
    if ((_v319 == _v224)) {
        bkr_str _v2037 = _v1959(_v425, _v869(_v563));
        bkr_str _v2038 = bkr_str_concat("function:", _v2037);
        _v1196 = _v2012(_v1196, _v2020(_v425, _v875(_v563), _v2038));
        _v434 _v1145 = _v872(_v563);
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v907(_v1145))) {
            _v341 _v1523 = _v913(_v1145, _v1172);
            _v1196 = _v2012(_v1196, _v2020(_v425, _v866(_v1523), _v2038));
            _v1172 = (_v1172 + 1);
        }
        _v1196 = _v2012(_v1196, _v2044(_v425, _v877(_v563), _v2038));
    } else {
        if ((_v319 == _v249)) {
            _v1196 = _v2012(_v1196, _v2020(_v425, _v882(_v563), _v2035));
            _v1196 = _v2012(_v1196, _v2042(_v425, _v885(_v563), _v2035));
        } else {
            if ((_v319 == _v260)) {
                _v1196 = _v2012(_v1196, _v2020(_v425, _v1181(_v563), _v2035));
            } else {
                if ((_v319 == _v254)) {
                    bkr_str _v2039 = bkr_str_concat("struct:", _v1959(_v425, _v887(_v563)));
                    _v434 _v1162 = _v890(_v563);
                    bkr_i64 _v1172 = 0;
                    while ((_v1172 < _v907(_v1162))) {
                        _v341 _v1447 = _v913(_v1162, _v1172);
                        _v1196 = _v2012(_v1196, _v2020(_v425, _v895(_v1447), _v2039));
                        _v1172 = (_v1172 + 1);
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2050(bkr_i64 _v0) {
    return _v2051(_v477(_v0));
}

bkr_str _v2051(_v341 _v1546) {
    bkr_i64 _v425 = _v904(_v1546);
    bkr_str _v2035 = bkr_str_concat("kernel:", _v1959(_v425, _v664(_v1546)));
    bkr_str _v1196 = "[";
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        _v1196 = _v2012(_v1196, _v2049(_v1546, _v563, _v2035));
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2052(bkr_i64 _v0) {
    bkr_str _v1955 = ",";
    _v341 _v1546 = _v477(_v0);
    bkr_i64 _v425 = _v904(_v1546);
    _v434 _v1186 = _v899(_v1546);
    bkr_bool _v2007 = _v1947(_v1546);
    bkr_str _v2053 = "[]";
    bkr_str _v2054 = "[]";
    if (_v2007) {
        _v2053 = _v2041(_v1546);
        _v2054 = _v2051(_v1546);
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.self_host.symbol_table.v1")), _v1955), _v1907("representation", "bootstrap_ast_walk")), _v1955), _v1909("complete", BKR_FALSE)), _v1955), _v1909("declarations", _v2007)), _v1955), _v1909("references", _v2007)), _v1955), _v1909("truncated", (!_v2007))), _v1955), _v1907("scope_model", "bootstrap kernel/function/struct scopes paired with BUNKER_RESOLVER_JSON validation")), _v1955), _v1907("known_limits", "Derived from AST names and paired with BUNKER_RESOLVER_JSON for bootstrap duplicate/unresolved diagnostics; imports, visibility, overloads, and related definition-use spans are not complete yet. Full declaration/reference tables are omitted when interned names exceed AST_REPORT_FULL_WALK_NAME_LIMIT so stage1 compile of bkrc stays inside runner memory.")), _v1955), _v1907("resolver_report", "BUNKER_RESOLVER_JSON")), _v1955), _v1910("summary", bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1908("interned_name_count", vec_len(_v425))), _v1955), _v1908("function_count", _v1983(_v1186, _v224))), _v1955), _v1908("struct_count", _v1983(_v1186, _v254))), _v1955), _v1908("const_count", _v1983(_v1186, _v249))), "}"))), _v1955), _v1910("declaration_table", _v2053)), _v1955), _v1910("reference_table", _v2054)), "}");
}

bkr_str _v2055(bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_SYMBOL_TABLE_JSON: ", _v2052(_v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v2056(bkr_i64 _v319, bkr_str _v1212) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("type_kind", _v327(_v319))), _v1955), _v1908("type_tag", _v319)), _v1955), _v1907("c_abi", _v1650(_v319))), _v1955), _v1907("source", _v1212)), _v1955), _v1909("known", (_v319 != _v316))), "}");
}

bkr_str _v2057(bkr_i64 _v425, bkr_i64 _v516, bkr_str _v1212) {
    if (_v524(_v516)) {
        return _v2056(_v316, _v1212);
    }
    return _v2058(_v425, _v517(_v516), _v1212);
}

bkr_str _v2058(bkr_i64 _v425, _v346 _v521, bkr_str _v1212) {
    bkr_str _v1955 = ",";
    bkr_i64 _v319 = _v530(_v521);
    bkr_str _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("type_kind", _v327(_v319))), _v1955), _v1908("type_tag", _v319)), _v1955), _v1907("c_abi", _v1650(_v319))), _v1955), _v1907("source", _v1212)), _v1955), _v1909("known", (_v319 != _v316)));
    if ((_v319 == _v309)) {
        _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("struct_name", _v1959(_v425, _v532(_v521))));
    } else {
        if ((_v319 == _v308)) {
            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("element_type_kind", _v327(_v533(_v521)))), _v1955), _v1908("array_len", _v534(_v521)));
        } else {
            if ((_v319 == _v310)) {
                bkr_i64 _v954 = _v535(_v521);
                bkr_i64 _v1376 = _v536(_v521);
                _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("element_type_kind", _v327(_v954)));
                if (((_v954 == _v309) && (_v1376 >= 0))) {
                    _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("element_struct_name", _v1959(_v425, _v1376)));
                }
            } else {
                if ((_v319 == _v311)) {
                    bkr_i64 _v1378 = _v535(_v521);
                    bkr_i64 _v1380 = _v536(_v521);
                    _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("key_type_kind", _v327(_v1378))), _v1955), _v1907("value_type_kind", _v327(_v1380)));
                } else {
                    if ((_v319 == _v312)) {
                        bkr_i64 _v1382 = _v535(_v521);
                        bkr_i64 _v1383 = _v536(_v521);
                        _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("inner_type_kind", _v327(_v1382)));
                        if (((_v1382 == _v309) && (_v1383 >= 0))) {
                            _v1196 = bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("inner_struct_name", _v1959(_v425, _v1383)));
                        }
                    } else {
                        if ((_v319 == _v313)) {
                            bkr_i64 _v1385 = _v535(_v521);
                            bkr_i64 _v1387 = _v536(_v521);
                            _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1196, _v1955), _v1907("ok_type_kind", _v327(_v1385))), _v1955), _v1907("err_type_kind", _v327(_v1387)));
                        }
                    }
                }
            }
        }
    }
    return bkr_str_concat(_v1196, "}");
}

bkr_str _v2059(bkr_i64 _v1254, bkr_i64 _v1671) {
    return _v2060(_v1564(_v1254), _v1671);
}

bkr_str _v2060(_v1547 _v1254, bkr_i64 _v1671) {
    if (_v524(_v1671)) {
        return _v2056(_v316, "absent");
    }
    return _v2061(_v1254, _v538(_v1671));
}

bkr_str _v2061(_v1547 _v1254, _v426 _v542) {
    return _v2056(_v1669(_v1254, _v542), "bootstrap_inferred");
}

bkr_i64 _v2062(bkr_i64 _v1254, bkr_i64 _v516, bkr_i64 _v1671) {
    return _v2063(_v1564(_v1254), _v516, _v1671);
}

bkr_i64 _v2063(_v1547 _v1254, bkr_i64 _v516, bkr_i64 _v1671) {
    if (_v526(_v516)) {
        bkr_i64 _v1567 = _v1568(_v1254);
        if ((_v1567 != 0)) {
            return _v2064(_v507(_v1567), _v517(_v516));
        }
        return _v530(_v517(_v516));
    }
    if (_v526(_v1671)) {
        return _v1669(_v1254, _v538(_v1671));
    }
    return _v316;
}

bkr_i64 _v2065(bkr_i64 _v1254, bkr_i64 _v355, bkr_i64 _v516) {
    if (_v526(_v516)) {
        _v2066(_v1564(_v1254), _v355, _v517(_v516));
    }
    return _v1254;
}

_v1547 _v2066(_v1547 _v1254, bkr_i64 _v355, _v346 _v521) {
    if ((_v530(_v521) == _v308)) {
        _v1627(_v1254, _v355, _v533(_v521), _v534(_v521));
    }
    if ((_v530(_v521) == _v310)) {
        bkr_i64 _v1703 = _v533(_v521);
        if (((_v1703 != _v316) && (_v1703 != 0))) {
            _v1627(_v1254, _v355, _v1703, 0);
        }
    }
    return _v1254;
}

bkr_i64 _v2067(bkr_i64 _v0) {
    return _v1550(_v2068(_v477(_v0)));
}

_v1547 _v2068(_v341 _v1546) {
    bkr_i64 _v425 = _v904(_v1546);
    _v1547 _v1254 = _v1551(_v1959(_v425, _v664(_v1546)), _v425);
    _v1565(_v1254, _v508(_v1546));
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        bkr_i64 _v319 = _v569(_v563);
        if ((_v319 == _v224)) {
            bkr_i64 _v1146 = _v875(_v563);
            bkr_i64 _v1375 = _v307;
            if (_v526(_v1146)) {
                _v1375 = _v2064(_v1546, _v517(_v1146));
            }
            _v1623(_v1254, _v869(_v563), _v1375);
        } else {
            if ((_v319 == _v249)) {
                bkr_i64 _v2069 = _v2063(_v1254, _v882(_v563), _v885(_v563));
                _v1625(_v1254, _v879(_v563), _v2069);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_str _v2070(bkr_str _v1196, bkr_str _v558) {
    if ((bkr_len((bkr_str)(intptr_t)(_v1196)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1196, ","), _v558);
    }
    return bkr_str_concat(_v1196, _v558);
}

bkr_str _v2071(bkr_str _v1196, bkr_str _v423) {
    if ((bkr_len((bkr_str)(intptr_t)(_v423)) <= 2)) {
        return _v1196;
    }
    bkr_str _v2013 = substring(_v423, 1, (bkr_len((bkr_str)(intptr_t)(_v423)) - 1));
    if ((bkr_len((bkr_str)(intptr_t)(_v1196)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1196, ","), _v2013);
    }
    return bkr_str_concat(_v1196, _v2013);
}

bkr_str _v2072(bkr_i64 _v425, bkr_i64 _v1139) {
    return _v2073(_v425, _v477(_v1139));
}

bkr_str _v2073(bkr_i64 _v425, _v341 _v1523) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("name", _v1959(_v425, _v863(_v1523)))), _v1955), _v1908("source_start", _v512(_v1523))), _v1955), _v1908("source_end", _v513(_v1523))), _v1955), _v1910("declared_type", _v2057(_v425, _v866(_v1523), "declared"))), "}");
}

bkr_str _v2074(bkr_i64 _v425, bkr_i64 _v411) {
    return _v2075(_v425, _v605(_v411));
}

bkr_str _v2075(bkr_i64 _v425, _v434 _v1145) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1145))) {
        _v1196 = _v2070(_v1196, _v2073(_v425, _v913(_v1145, _v1172)));
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2076(bkr_i64 _v425, bkr_i64 _v1154) {
    return _v2077(_v425, _v477(_v1154));
}

bkr_str _v2077(bkr_i64 _v425, _v341 _v1447) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("name", _v1959(_v425, _v892(_v1447)))), _v1955), _v1908("source_start", _v512(_v1447))), _v1955), _v1908("source_end", _v513(_v1447))), _v1955), _v1910("declared_type", _v2057(_v425, _v895(_v1447), "declared"))), "}");
}

bkr_str _v2078(bkr_i64 _v425, bkr_i64 _v416) {
    return _v2079(_v425, _v605(_v416));
}

bkr_str _v2079(bkr_i64 _v425, _v434 _v1162) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1162))) {
        _v1196 = _v2070(_v1196, _v2077(_v425, _v913(_v1162, _v1172)));
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2080(bkr_i64 _v425, bkr_i64 _v558) {
    return _v2081(_v425, _v560(_v558));
}

bkr_str _v2081(bkr_i64 _v425, _v428 _v563) {
    _v341 _v1981 = _v588(_v563);
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("name", _v1959(_v425, _v887(_v563)))), _v1955), _v1908("source_start", _v512(_v1981))), _v1955), _v1908("source_end", _v513(_v1981))), _v1955), _v1910("fields", _v2079(_v425, _v890(_v563)))), "}");
}

bkr_str _v2082(bkr_i64 _v0) {
    return _v2083(_v477(_v0));
}

bkr_str _v2083(_v341 _v1546) {
    bkr_i64 _v425 = _v904(_v1546);
    bkr_str _v1196 = "[";
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v254)) {
            _v1196 = _v2070(_v1196, _v2081(_v425, _v563));
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2084(bkr_i64 _v1254, bkr_i64 _v425, bkr_i64 _v558) {
    return _v2085(_v1564(_v1254), _v425, _v560(_v558));
}

bkr_str _v2085(_v1547 _v1254, bkr_i64 _v425, _v428 _v563) {
    _v341 _v1981 = _v588(_v563);
    bkr_str _v1955 = ",";
    bkr_i64 _v516 = _v882(_v563);
    bkr_i64 _v387 = _v885(_v563);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("name", _v1959(_v425, _v879(_v563)))), _v1955), _v1908("source_start", _v512(_v1981))), _v1955), _v1908("source_end", _v513(_v1981))), _v1955), _v1910("declared_type", _v2057(_v425, _v516, "declared"))), _v1955), _v1910("inferred_type", _v2060(_v1254, _v387))), _v1955), _v1910("effective_type", _v2056(_v2063(_v1254, _v516, _v387), "effective"))), "}");
}

bkr_str _v2086(bkr_i64 _v0, bkr_i64 _v1254) {
    return _v2087(_v477(_v0), _v1564(_v1254));
}

bkr_str _v2087(_v341 _v1546, _v1547 _v1254) {
    bkr_i64 _v425 = _v904(_v1546);
    bkr_str _v1196 = "[";
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v249)) {
            _v1196 = _v2070(_v1196, _v2085(_v1254, _v425, _v563));
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2088(bkr_i64 _v1254, bkr_i64 _v425, bkr_i64 _v370) {
    return _v2089(_v1564(_v1254), _v425, _v551(_v370));
}

bkr_str _v2089(_v1547 _v1254, bkr_i64 _v425, _v427 _v554) {
    _v341 _v2090 = _v587(_v554);
    bkr_str _v1955 = ",";
    bkr_i64 _v516 = _v761(_v554);
    bkr_i64 _v366 = _v764(_v554);
    bkr_i64 _v2091 = _v2063(_v1254, _v516, _v366);
    bkr_str _v1196 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("name", _v1959(_v425, _v758(_v554)))), _v1955), _v1908("source_start", _v512(_v2090))), _v1955), _v1908("source_end", _v513(_v2090))), _v1955), _v1910("declared_type", _v2057(_v425, _v516, "declared"))), _v1955), _v1910("inferred_type", _v2060(_v1254, _v366))), _v1955), _v1910("effective_type", _v2056(_v2091, "effective")));
    return bkr_str_concat(_v1196, "}");
}

bkr_i64 _v2092(bkr_i64 _v1254, bkr_i64 _v370) {
    _v2093(_v1564(_v1254), _v551(_v370));
    return _v1254;
}

_v1547 _v2093(_v1547 _v1254, _v427 _v554) {
    bkr_i64 _v516 = _v761(_v554);
    bkr_i64 _v366 = _v764(_v554);
    bkr_i64 _v319 = _v2063(_v1254, _v516, _v366);
    bkr_i64 _v355 = _v758(_v554);
    _v1608(_v1254, _v355, _v319);
    if (_v526(_v516)) {
        _v2066(_v1254, _v355, _v517(_v516));
    } else {
        if (_v526(_v366)) {
            _v426 _v1709 = _v538(_v366);
            bkr_i64 _v1710 = _v545(_v1709);
            if ((_v1710 == _v252)) {
                _v434 _v995 = _v702(_v1709);
                bkr_i64 _v1707 = _v907(_v995);
                if ((_v1707 > 0)) {
                    bkr_i64 _v954 = _v1669(_v1254, _v538(_v910(_v995, 0)));
                    _v1627(_v1254, _v355, _v954, _v1707);
                }
            } else {
                if ((_v1710 == _v239)) {
                    bkr_i64 _v1707 = _v707(_v1709);
                    bkr_i64 _v954 = _v1669(_v1254, _v705(_v1709));
                    _v1627(_v1254, _v355, _v954, _v1707);
                }
            }
        }
    }
    return _v1254;
}

bkr_str _v2094(bkr_i64 _v1254, bkr_i64 _v425, bkr_i64 _v578) {
    return _v2095(_v1564(_v1254), _v425, _v580(_v578));
}

bkr_str _v2095(_v1547 _v1254, bkr_i64 _v425, _v429 _v583) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        _v427 _v554 = _v1111(_v583, _v1172);
        bkr_i64 _v319 = _v556(_v554);
        if ((_v319 == _v228)) {
            _v1196 = _v2070(_v1196, _v2089(_v1254, _v425, _v554));
            _v2093(_v1254, _v554);
        } else {
            if ((_v319 == _v230)) {
                _v1196 = _v2071(_v1196, _v2095(_v1254, _v425, _v830(_v554)));
                bkr_i64 _v377 = _v833(_v554);
                if (_v526(_v377)) {
                    _v1196 = _v2071(_v1196, _v2095(_v1254, _v425, _v579(_v377)));
                }
            } else {
                if ((_v319 == _v231)) {
                    _v1196 = _v2071(_v1196, _v2095(_v1254, _v425, _v852(_v554)));
                } else {
                    if ((_v319 == _v236)) {
                        _v1608(_v1254, _v835(_v554), _v303);
                        _v1196 = _v2071(_v1196, _v2095(_v1254, _v425, _v845(_v554)));
                    } else {
                        if ((_v319 == _v237)) {
                            _v1196 = _v2071(_v1196, _v2095(_v1254, _v425, _v847(_v554)));
                        }
                    }
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2096(bkr_i64 _v1254, bkr_i64 _v370) {
    return _v2097(_v1564(_v1254), _v551(_v370));
}

bkr_str _v2097(_v1547 _v1254, _v427 _v554) {
    _v341 _v2090 = _v587(_v554);
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1908("source_start", _v512(_v2090))), _v1955), _v1908("source_end", _v513(_v2090))), _v1955), _v1910("expr_type", _v2060(_v1254, _v769(_v554)))), "}");
}

bkr_str _v2098(bkr_i64 _v1254, bkr_i64 _v425, bkr_i64 _v578) {
    return _v2099(_v1564(_v1254), _v425, _v580(_v578));
}

bkr_str _v2099(_v1547 _v1254, bkr_i64 _v425, _v429 _v583) {
    bkr_str _v1196 = "[";
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        _v427 _v554 = _v1111(_v583, _v1172);
        bkr_i64 _v319 = _v556(_v554);
        if ((_v319 == _v229)) {
            _v1196 = _v2070(_v1196, _v2097(_v1254, _v554));
        } else {
            if ((_v319 == _v230)) {
                _v1196 = _v2071(_v1196, _v2099(_v1254, _v425, _v830(_v554)));
                bkr_i64 _v377 = _v833(_v554);
                if (_v526(_v377)) {
                    _v1196 = _v2071(_v1196, _v2099(_v1254, _v425, _v579(_v377)));
                }
            } else {
                if ((_v319 == _v231)) {
                    _v1196 = _v2071(_v1196, _v2099(_v1254, _v425, _v852(_v554)));
                } else {
                    if ((_v319 == _v236)) {
                        _v1196 = _v2071(_v1196, _v2099(_v1254, _v425, _v845(_v554)));
                    } else {
                        if ((_v319 == _v237)) {
                            _v1196 = _v2071(_v1196, _v2099(_v1254, _v425, _v847(_v554)));
                        }
                    }
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_i64 _v2100(bkr_i64 _v0, bkr_i64 _v930) {
    return _v1550(_v2101(_v477(_v0), _v560(_v930)));
}

_v1547 _v2101(_v341 _v1546, _v428 _v1530) {
    _v1547 _v1254 = _v2068(_v1546);
    _v434 _v1145 = _v872(_v1530);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1145))) {
        _v341 _v1523 = _v913(_v1145, _v1172);
        bkr_i64 _v2102 = _v866(_v1523);
        bkr_i64 _v2103 = _v863(_v1523);
        bkr_i64 _v2104 = _v303;
        if (_v526(_v2102)) {
            _v2104 = _v2064(_v1546, _v517(_v2102));
        }
        _v1608(_v1254, _v2103, _v2104);
        if (_v526(_v2102)) {
            _v2066(_v1254, _v2103, _v517(_v2102));
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_str _v2105(bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v558) {
    return _v2106(_v477(_v0), _v425, _v560(_v558));
}

bkr_str _v2106(_v341 _v1546, bkr_i64 _v425, _v428 _v563) {
    _v341 _v1981 = _v588(_v563);
    bkr_str _v1955 = ",";
    _v1547 _v1254 = _v2101(_v1546, _v563);
    _v429 _v1127 = _v877(_v563);
    bkr_str _v2107 = _v2095(_v1254, _v425, _v1127);
    bkr_str _v2108 = _v2099(_v1254, _v425, _v1127);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("name", _v1959(_v425, _v869(_v563)))), _v1955), _v1908("source_start", _v512(_v1981))), _v1955), _v1908("source_end", _v513(_v1981))), _v1955), _v1910("return_type", _v2057(_v425, _v875(_v563), "declared"))), _v1955), _v1910("params", _v2075(_v425, _v872(_v563)))), _v1955), _v1910("locals", _v2107)), _v1955), _v1910("returns", _v2108)), "}");
}

bkr_str _v2109(bkr_i64 _v0) {
    return _v2110(_v477(_v0));
}

bkr_str _v2110(_v341 _v1546) {
    bkr_i64 _v425 = _v904(_v1546);
    bkr_str _v1196 = "[";
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v224)) {
            _v1196 = _v2070(_v1196, _v2106(_v1546, _v425, _v563));
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2111(bkr_i64 _v0) {
    bkr_str _v1955 = ",";
    _v341 _v1546 = _v477(_v0);
    _v434 _v1186 = _v899(_v1546);
    bkr_bool _v2007 = _v1947(_v1546);
    bkr_str _v2112 = "[]";
    bkr_str _v2113 = "[]";
    bkr_str _v2114 = "[]";
    if (_v2007) {
        _v1547 _v1254 = _v2068(_v1546);
        _v2112 = _v2083(_v1546);
        _v2113 = _v2087(_v1546, _v1254);
        _v2114 = _v2110(_v1546);
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.self_host.type_graph.v1")), _v1955), _v1907("representation", "bootstrap_codegen_inference")), _v1955), _v1909("complete", BKR_FALSE)), _v1955), _v1909("declared_types", _v2007)), _v1955), _v1909("local_inference", _v2007)), _v1955), _v1909("truncated", (!_v2007))), _v1955), _v1907("known_limits", "Derived from declarations plus bootstrap C codegen inference; no real Bunker typechecker, generic graph, trait constraints, exhaustiveness graph, or cross-module type graph yet. Detail arrays are omitted when interned names exceed AST_REPORT_FULL_WALK_NAME_LIMIT.")), _v1955), _v1910("summary", bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1908("function_count", _v1983(_v1186, _v224))), _v1955), _v1908("struct_count", _v1983(_v1186, _v254))), _v1955), _v1908("const_count", _v1983(_v1186, _v249))), "}"))), _v1955), _v1910("structs", _v2112)), _v1955), _v1910("constants", _v2113)), _v1955), _v1910("functions", _v2114)), "}");
}

bkr_str _v2115(bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_TYPE_GRAPH_JSON: ", _v2111(_v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v2116(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v1950, bkr_i64 _v1951, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117) {
    return _v2118(_v319, _v1244, _v1363, _v2015, _v1950, _v1951, _v1279, _v1282, "[]", _v2117);
}

bkr_str _v2118(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v1950, bkr_i64 _v1951, bkr_str _v1279, bkr_str _v1282, bkr_str _v2119, bkr_str _v2117) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("phase", "resolver")), _v1955), _v1907("kind", _v319)), _v1955), _v1907("rule_id", _v319)), _v1955), _v1907("error_code", _v1244)), _v1955), _v1907("severity", "error")), _v1955), _v1907("name", _v1363)), _v1955), _v1907("scope", _v2015)), _v1955), _v1908("source_start", _v1950)), _v1955), _v1908("source_end", _v1951)), _v1955), _v1909("span_known", ((_v1950 != _v268) && (_v1951 != _v268)))), _v1955), _v1907("expected", _v1279)), _v1955), _v1907("actual", _v1282)), _v1955), _v1910("related_declarations", _v2119)), _v1955), _v1907("suggested_action", _v2117)), _v1955), _v1907("fix_applicability", "manual_review")), _v1955), _v1907("fix_confidence", "medium")), _v1955), _v1909("safe_edit_available", BKR_FALSE)), _v1955), _v1910("suggested_edits", _v1956())), _v1955), _v1907("repair_hint", _v2117)), "}");
}

bkr_str _v2120(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117) {
    return _v2121(_v319, _v1244, _v1363, _v2015, _v477(_v447), _v1279, _v1282, _v2117);
}

bkr_str _v2121(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117) {
    return _v2122(_v319, _v1244, _v1363, _v2015, _v452, _v1279, _v1282, "[]", _v2117);
}

bkr_str _v2122(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_str _v1279, bkr_str _v1282, bkr_str _v2119, bkr_str _v2117) {
    return _v2118(_v319, _v1244, _v1363, _v2015, _v512(_v452), _v513(_v452), _v1279, _v1282, _v2119, _v2117);
}

bkr_str _v2123(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v463, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117) {
    return _v2124(_v319, _v1244, _v1363, _v2015, _v593(_v463), _v1279, _v1282, _v2117);
}

bkr_str _v2124(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, _v433 _v473, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117) {
    return _v2116(_v319, _v1244, _v1363, _v2015, _v602(_v473), _v603(_v473), _v1279, _v1282, _v2117);
}

bkr_i64 _v2125(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_str _v2126, bkr_i64 _v447) {
    return _v2127(_v1254, _v1363, _v2015, _v2126, _v477(_v447));
}

bkr_i64 _v2127(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_str _v2126, _v341 _v452) {
    bkr_str _v2128 = bkr_str_concat(bkr_str_concat("Rename this ", _v2126), " or remove the earlier declaration with the same name in this scope.");
    return _v1964(_v1254, _v2121("duplicate_declaration", "BKR_SELF_DUPLICATE_SYMBOL", _v1363, _v2015, _v452, bkr_str_concat(bkr_str_concat("unique ", _v2126), " name"), _v1363, _v2128));
}

bkr_i64 _v2129(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v463) {
    return _v2130(_v1254, _v1363, _v2015, _v593(_v463));
}

bkr_i64 _v2130(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v433 _v473) {
    bkr_str _v2128 = "Rename this pattern binding or remove the earlier binding with the same name in this pattern scope.";
    return _v1964(_v1254, _v2124("duplicate_declaration", "BKR_SELF_DUPLICATE_SYMBOL", _v1363, _v2015, _v473, "unique pattern binding", _v1363, _v2128));
}

bkr_i64 _v2131(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_str _v2132, bkr_i64 _v447, bkr_str _v1279) {
    return _v2133(_v1254, _v1363, _v2015, _v2132, _v477(_v447), _v1279);
}

bkr_i64 _v2133(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_str _v2132, _v341 _v452, bkr_str _v1279) {
    return _v2134(_v1254, _v1363, _v2015, _v2132, _v452, _v1279, "[]");
}

bkr_i64 _v2134(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, bkr_str _v2132, _v341 _v452, bkr_str _v1279, bkr_str _v2119) {
    bkr_str _v2128 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Declare ", _v1363), " in scope "), _v2015), ", import it through a real module, or correct the misspelled reference.");
    return _v1964(_v1254, _v2122("unresolved_reference", "BKR_SELF_UNRESOLVED_SYMBOL", _v1363, _v2015, _v452, _v1279, bkr_str_concat(bkr_str_concat(_v2132, " "), _v1363), _v2119, _v2128));
}

bkr_str _v2135(bkr_str _v1196, bkr_str _v558) {
    if ((bkr_len((bkr_str)(intptr_t)(_v1196)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1196, ","), _v558);
    }
    return bkr_str_concat(_v1196, _v558);
}

bkr_str _v2136(bkr_str _v319, bkr_str _v1363, _v341 _v452) {
    bkr_str _v1955 = ",";
    bkr_i64 _v1950 = _v512(_v452);
    bkr_i64 _v1951 = _v513(_v452);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("kind", _v319)), _v1955), _v1907("name", _v1363)), _v1955), _v1908("source_start", _v1950)), _v1955), _v1908("source_end", _v1951)), _v1955), _v1909("span_known", ((_v1950 != _v268) && (_v1951 != _v268)))), "}");
}

bkr_str _v2137(_v341 _v1546, bkr_i64 _v425) {
    bkr_str _v1196 = "[";
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v224)) {
            _v1196 = _v2135(_v1196, _v2136("function", _v1959(_v425, _v869(_v563)), _v588(_v563)));
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2138(_v341 _v1546, bkr_i64 _v425) {
    bkr_str _v1196 = "[";
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v249)) {
            _v1196 = _v2135(_v1196, _v2136("const", _v1959(_v425, _v879(_v563)), _v588(_v563)));
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2139(_v341 _v1546, bkr_i64 _v425) {
    bkr_str _v1196 = "[";
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v254)) {
            _v1196 = _v2135(_v1196, _v2136("struct", _v1959(_v425, _v887(_v563)), _v588(_v563)));
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2140(_v341 _v1546, bkr_i64 _v425, bkr_i64 _v1519) {
    bkr_str _v1196 = "[";
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v254) && (_v887(_v563) == _v1519))) {
            _v434 _v1162 = _v890(_v563);
            bkr_i64 _v1645 = 0;
            while ((_v1645 < _v907(_v1162))) {
                _v341 _v1447 = _v913(_v1162, _v1645);
                _v1196 = _v2135(_v1196, _v2136("field", _v1959(_v425, _v892(_v1447)), _v1447));
                _v1645 = (_v1645 + 1);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_bool _v2141(bkr_str _v1363) {
    if (bkr_str_eq(_v1363, "Some")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "len")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "strlen")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "print")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "println")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "log")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "read_file")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "write_file")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "file_exists")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "file_set_executable")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_new")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_push")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_set")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_len")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_pop")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_clear")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_new")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_insert")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_contains")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_remove")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_keys")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_len")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_clear")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "char_at")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "char_code")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "char_code_at")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "substring")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "contains")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "starts_with")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "ends_with")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "trim")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "parse_int")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "parse_int_result")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "read_file_result")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "str_index_of")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "str_replace")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "str_split")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "str_to_upper")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "str_to_lower")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "str_repeat")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "path_join")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "path_dir")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "path_base")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "path_ext")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "path_is_abs")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "env_var")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "env_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "env_set")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "env_has")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "time_now_ms")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "time_now_unix")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "runtime_version_major")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "runtime_version_minor")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "runtime_version_patch")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "runtime_version_str")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bytes_new")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bytes_len")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bytes_capacity")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bytes_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bytes_set")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bytes_push")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bytes_from_str")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bytes_to_str")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "slice_new")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "slice_len")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "slice_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "slice_sub")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "slice_to_vec")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "slice_contains")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_as_slice")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_slice")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bytes_as_slice")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bytes_slice")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "path_exists")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "path_is_file")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "path_is_dir")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "file_read")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "file_write")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "file_size")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "file_remove")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "file_read_bytes")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "file_write_bytes")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "dir_create")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "dir_remove")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "process_run")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "process_run_status")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "process_exit")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "process_pid")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "process_is_sandboxed")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "write_file_result")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_get_opt")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_get_opt")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_pop_opt")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_contains")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_is_empty")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_clone")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_reverse")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_is_empty")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "hashmap_values")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_map")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_filter")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_fold")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "vec_find")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "Ok")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "Err")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "panic")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "assert")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "int_to_string")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "from_char_code")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "join_lines")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "result_ok")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "result_err")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "result_is_ok")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "result_is_err")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "result_unwrap")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "result_unwrap_err")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "result_tag")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "result_value")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bkr_tuple2")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bkr_tuple3")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "bkr_tuple_get")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "args_count")) {
        return BKR_TRUE;
    }
    if (bkr_str_eq(_v1363, "arg_at")) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2142(bkr_i64 _v0, bkr_i64 _v355) {
    return _v2143(_v477(_v0), _v355);
}

bkr_bool _v2143(_v341 _v1546, bkr_i64 _v355) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v224) && (_v869(_v563) == _v355))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2144(bkr_i64 _v0, bkr_i64 _v355) {
    return _v2145(_v477(_v0), _v355);
}

bkr_bool _v2145(_v341 _v1546, bkr_i64 _v355) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v249) && (_v879(_v563) == _v355))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2146(bkr_i64 _v0, bkr_i64 _v355) {
    return _v2147(_v477(_v0), _v355);
}

bkr_bool _v2148(_v341 _v1546, bkr_i64 _v355) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v260) && (_v1180(_v563) == _v355))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2147(_v341 _v1546, bkr_i64 _v355) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v254) && (_v887(_v563) == _v355))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2149(_v341 _v1546, bkr_i64 _v355) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v259) && (_v1168(_v563) == _v355))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2150(bkr_i64 _v0, bkr_i64 _v1519, bkr_i64 _v1674) {
    return _v2151(_v477(_v0), _v1519, _v1674);
}

bkr_bool _v2151(_v341 _v1546, bkr_i64 _v1519, bkr_i64 _v1674) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v254) && (_v887(_v563) == _v1519))) {
            _v434 _v1162 = _v890(_v563);
            bkr_i64 _v1645 = 0;
            while ((_v1645 < _v907(_v1162))) {
                _v341 _v1447 = _v913(_v1162, _v1645);
                if ((_v892(_v1447) == _v1674)) {
                    return BKR_TRUE;
                }
                _v1645 = (_v1645 + 1);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2152(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v516, bkr_str _v2015) {
    return _v2153(_v1254, _v477(_v0), _v425, _v516, _v2015);
}

bkr_i64 _v2153(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, bkr_i64 _v516, bkr_str _v2015) {
    if (_v526(_v516)) {
        _v1254 = _v2154(_v1254, _v1546, _v425, _v517(_v516), _v2015);
    }
    return _v1254;
}

bkr_i64 _v2154(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v346 _v521, bkr_str _v2015) {
    if ((_v530(_v521) == _v309)) {
        bkr_i64 _v355 = _v532(_v521);
        if ((((!_v2147(_v1546, _v355)) && (!_v2148(_v1546, _v355))) && (!_v2149(_v1546, _v355)))) {
            _v1254 = _v2134(_v1254, _v1959(_v425, _v355), _v2015, "type_reference", _v586(_v521), "declared struct type", _v2139(_v1546, _v425));
        }
    }
    return _v1254;
}

bkr_i64 _v2155(bkr_i64 _v1254, bkr_i64 _v425, bkr_i64 _v463, bkr_str _v2015, bkr_i64 _v2156) {
    return _v2157(_v1254, _v425, _v593(_v463), _v2015, _v2156);
}

bkr_i64 _v2157(bkr_i64 _v1254, bkr_i64 _v425, _v433 _v473, bkr_str _v2015, bkr_i64 _v2156) {
    bkr_i64 _v319 = _v597(_v473);
    if (((((_v319 == _v285) || (_v319 == _v287)) || (_v319 == _v290)) || (_v319 == _v291))) {
        bkr_i64 _v355 = _v598(_v473);
        if ((_v355 >= 0)) {
            if (_v1965(_v2156, _v355)) {
                _v1254 = _v2130(_v1254, _v1959(_v425, _v355), _v2015, _v473);
            } else {
                vec_push(_v2156, _v355);
            }
        }
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            _v433 _v1408 = _v592(_v345);
            _v1254 = _v2157(_v1254, _v425, _v1408, _v2015, _v2156);
        }
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            bkr_i64 _v1390 = ((bkr_i64)(_v345));
            bkr_i64 _v1172 = 0;
            while ((_v1172 < vec_len(_v1390))) {
                _v433 _v1408 = _v592(vec_get(_v1390, _v1172));
                _v1254 = _v2157(_v1254, _v425, _v1408, _v2015, _v2156);
                _v1172 = (_v1172 + 1);
            }
        } else {
            bkr_i64 _v2024 = _v600(_v473);
            bkr_i64 _v2025 = _v601(_v473);
            bkr_i64 _v2026 = _v598(_v473);
            if ((_v2024 >= 0)) {
                vec_push(_v2156, _v2024);
            }
            if ((_v2025 >= 0)) {
                vec_push(_v2156, _v2025);
            }
            if ((_v2026 >= 0)) {
                vec_push(_v2156, _v2026);
            }
        }
    }
    if ((_v319 == _v293)) {
        bkr_i64 _v2024 = _v600(_v473);
        bkr_i64 _v2025 = _v601(_v473);
        bkr_i64 _v2026 = _v599(_v473);
        if ((_v2024 >= 0)) {
            vec_push(_v2156, _v2024);
        }
        if ((_v2025 >= 0)) {
            vec_push(_v2156, _v2025);
        }
        if ((_v2026 >= 0)) {
            vec_push(_v2156, _v2026);
        }
    }
    if ((_v319 == _v289)) {
        bkr_i64 _v2024 = _v600(_v473);
        bkr_i64 _v2025 = _v601(_v473);
        if ((_v2024 >= 0)) {
            vec_push(_v2156, _v2024);
        }
        if ((_v2025 >= 0)) {
            vec_push(_v2156, _v2025);
        }
    }
    return _v1254;
}

bkr_i64 _v2158(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v1671, bkr_str _v2015, bkr_i64 _v2156) {
    return _v2159(_v1254, _v477(_v0), _v425, _v1671, _v2015, _v2156);
}

bkr_i64 _v2159(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, bkr_i64 _v1671, bkr_str _v2015, bkr_i64 _v2156) {
    if (_v524(_v1671)) {
        return _v1254;
    }
    return _v2160(_v1254, _v1546, _v425, _v538(_v1671), _v2015, _v2156);
}

bkr_i64 _v2160(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v426 _v542, bkr_str _v2015, bkr_i64 _v2156) {
    _v341 _v2161 = _v547(_v542);
    bkr_i64 _v319 = _v545(_v542);
    if ((_v319 == _v245)) {
        bkr_i64 _v355 = _v663(_v542);
        bkr_str _v1363 = _v1959(_v425, _v355);
        if ((((((!bkr_str_eq(_v1363, "None")) && (!_v1965(_v2156, _v355))) && (!_v2145(_v1546, _v355))) && (!_v2149(_v1546, _v355))) && (bkr_str_index_of((bkr_str)(intptr_t)(_v1363), (bkr_str)(intptr_t)("::")) < 0))) {
            _v1254 = _v2134(_v1254, _v1363, _v2015, "identifier", _v2161, "local, parameter, for binding, pattern binding, or constant", _v2138(_v1546, _v425));
        }
    } else {
        if ((_v319 == _v261)) {
            _v426 _v1022 = _v695(_v542);
            _v1254 = _v2160(_v1254, _v1546, _v425, _v1022, _v2015, _v2156);
            _v434 _v1016 = _v699(_v542);
            bkr_i64 _v1172 = 0;
            while ((_v1172 < _v907(_v1016))) {
                _v341 _v1440 = _v913(_v1016, _v1172);
                _v1254 = _v2160(_v1254, _v1546, _v425, _v540(_v1440), _v2015, _v2156);
                _v1172 = (_v1172 + 1);
            }
        } else {
            if ((_v319 == _v244)) {
                bkr_i64 _v355 = _v689(_v542);
                bkr_str _v1363 = _v1959(_v425, _v355);
                if ((((!_v2141(_v1363)) && (!_v2143(_v1546, _v355))) && (!_v2147(_v1546, _v355)))) {
                    _v1254 = _v2134(_v1254, _v1363, _v2015, "function_call", _v2161, "declared function or supported bootstrap builtin", _v2137(_v1546, _v425));
                }
                _v434 _v1016 = _v692(_v542);
                bkr_i64 _v1172 = 0;
                while ((_v1172 < _v907(_v1016))) {
                    _v341 _v1440 = _v913(_v1016, _v1172);
                    _v1254 = _v2160(_v1254, _v1546, _v425, _v540(_v1440), _v2015, _v2156);
                    _v1172 = (_v1172 + 1);
                }
            } else {
                if ((_v319 == _v257)) {
                    bkr_i64 _v1519 = _v725(_v542);
                    bkr_str _v1697 = _v1959(_v425, _v1519);
                    if ((!_v2147(_v1546, _v1519))) {
                        _v1254 = _v2134(_v1254, _v1697, _v2015, "struct_literal", _v2161, "declared struct", _v2139(_v1546, _v425));
                    }
                    bkr_i64 _v2162 = vec_new();
                    _v435 _v1008 = _v728(_v542);
                    _v434 _v1009 = _v731(_v542);
                    bkr_i64 _v1172 = 0;
                    while ((_v1172 < _v916(_v1008))) {
                        bkr_i64 _v1674 = _v918(_v1008, _v1172);
                        bkr_str _v1045 = _v1959(_v425, _v1674);
                        if (_v1965(_v2162, _v1674)) {
                            _v1254 = _v2133(_v1254, _v1045, _v2015, "field_initializer", _v2161, "one initializer per field");
                        } else {
                            vec_push(_v2162, _v1674);
                            if ((_v2147(_v1546, _v1519) && (!_v2151(_v1546, _v1519, _v1674)))) {
                                _v1254 = _v2134(_v1254, _v1045, _v2015, "field_initializer", _v2161, bkr_str_concat("field declared on struct ", _v1697), _v2140(_v1546, _v425, _v1519));
                            }
                        }
                        _v341 _v1437 = _v913(_v1009, _v1172);
                        _v1254 = _v2160(_v1254, _v1546, _v425, _v540(_v1437), _v2015, _v2156);
                        _v1172 = (_v1172 + 1);
                    }
                    bkr_i64 _v403 = _v1006(_v542);
                    if ((_v403 != 0)) {
                        _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v403), _v2015, _v2156);
                    }
                } else {
                    if ((_v319 == _v256)) {
                        _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v720(_v542)), _v2015, _v2156);
                    } else {
                        if ((_v319 == _v242)) {
                            _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v675(_v542)), _v2015, _v2156);
                            _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v678(_v542)), _v2015, _v2156);
                        } else {
                            if ((_v319 == _v240)) {
                                _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v778(_v542)), _v2015, _v2156);
                            } else {
                                if ((_v319 == _v241)) {
                                    _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v782(_v542)), _v2015, _v2156);
                                    _v1254 = _v2154(_v1254, _v1546, _v425, _v517(_v783(_v542)), _v2015);
                                } else {
                                    if ((_v319 == _v243)) {
                                        _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v685(_v542)), _v2015, _v2156);
                                    } else {
                                        if ((_v319 == _v250)) {
                                            _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v734(_v542)), _v2015, _v2156);
                                            _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v737(_v542)), _v2015, _v2156);
                                            _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v740(_v542)), _v2015, _v2156);
                                        } else {
                                            if ((_v319 == _v239)) {
                                                _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v704(_v542)), _v2015, _v2156);
                                            } else {
                                                if ((_v319 == _v252)) {
                                                    _v434 _v995 = _v702(_v542);
                                                    bkr_i64 _v1172 = 0;
                                                    while ((_v1172 < _v907(_v995))) {
                                                        _v341 _v2030 = _v913(_v995, _v1172);
                                                        _v1254 = _v2160(_v1254, _v1546, _v425, _v540(_v2030), _v2015, _v2156);
                                                        _v1172 = (_v1172 + 1);
                                                    }
                                                } else {
                                                    if ((_v319 == _v253)) {
                                                        _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v712(_v542)), _v2015, _v2156);
                                                        _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v715(_v542)), _v2015, _v2156);
                                                    } else {
                                                        if ((_v319 == _v227)) {
                                                            _v1254 = _v2163(_v1254, _v1546, _v425, _v581(_v2161), _v2015, _v2156, _v1966());
                                                        } else {
                                                            if ((_v319 == _v258)) {
                                                                _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v743(_v542)), _v2015, _v2156);
                                                                _v436 _v621 = _v746(_v542);
                                                                _v434 _v976 = _v749(_v542);
                                                                _v435 _v977 = _v751(_v542);
                                                                bkr_i64 _v1172 = 0;
                                                                while ((_v1172 < _v920(_v621))) {
                                                                    bkr_i64 _v2164 = _v1967(_v2156);
                                                                    bkr_i64 _v2165 = vec_new();
                                                                    _v1254 = _v2157(_v1254, _v425, _v925(_v621, _v1172), _v2015, _v2165);
                                                                    bkr_i64 _v1645 = 0;
                                                                    while ((_v1645 < vec_len(_v2165))) {
                                                                        bkr_i64 _v2166 = vec_get(_v2165, _v1645);
                                                                        vec_push(_v2164, _v2166);
                                                                        _v1645 = (_v1645 + 1);
                                                                    }
                                                                    if ((_v1172 < _v916(_v977))) {
                                                                        bkr_i64 _v2167 = _v918(_v977, _v1172);
                                                                        if ((_v2167 != 0)) {
                                                                            _v1254 = _v2160(_v1254, _v1546, _v425, _v538(_v2167), _v2015, _v2164);
                                                                        }
                                                                    }
                                                                    _v341 _v1127 = _v913(_v976, _v1172);
                                                                    if ((_v510(_v1127) == _v227)) {
                                                                        _v1254 = _v2163(_v1254, _v1546, _v425, _v581(_v1127), _v2015, _v2164, _v1966());
                                                                    } else {
                                                                        _v1254 = _v2160(_v1254, _v1546, _v425, _v540(_v1127), _v2015, _v2164);
                                                                    }
                                                                    _v1172 = (_v1172 + 1);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1254;
}

bkr_i64 _v2168(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v370, bkr_str _v2015, bkr_i64 _v2156, bkr_i64 _v2169) {
    return _v2170(_v1254, _v477(_v0), _v425, _v551(_v370), _v2015, _v2156, _v2169);
}

bkr_i64 _v2170(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v427 _v554, bkr_str _v2015, bkr_i64 _v2156, bkr_i64 _v2169) {
    _v341 _v2090 = _v587(_v554);
    bkr_i64 _v319 = _v556(_v554);
    if ((_v319 == _v228)) {
        bkr_i64 _v355 = _v758(_v554);
        _v1254 = _v2153(_v1254, _v1546, _v425, _v761(_v554), _v2015);
        _v1254 = _v2159(_v1254, _v1546, _v425, _v764(_v554), _v2015, _v2156);
        if (_v1965(_v2169, _v355)) {
            _v1254 = _v2127(_v1254, _v1959(_v425, _v355), _v2015, "local", _v2090);
        } else {
            vec_push(_v2169, _v355);
        }
        vec_push(_v2156, _v355);
    } else {
        if ((_v319 == _v229)) {
            _v1254 = _v2159(_v1254, _v1546, _v425, _v769(_v554), _v2015, _v2156);
        } else {
            if ((_v319 == _v230)) {
                _v1254 = _v2159(_v1254, _v1546, _v425, _v828(_v554), _v2015, _v2156);
                _v1254 = _v2163(_v1254, _v1546, _v425, _v830(_v554), _v2015, _v2156, _v1966());
                bkr_i64 _v377 = _v833(_v554);
                if (_v526(_v377)) {
                    _v1254 = _v2163(_v1254, _v1546, _v425, _v579(_v377), _v2015, _v2156, _v1966());
                }
            } else {
                if ((_v319 == _v231)) {
                    _v1254 = _v2159(_v1254, _v1546, _v425, _v850(_v554), _v2015, _v2156);
                    _v1254 = _v2163(_v1254, _v1546, _v425, _v852(_v554), _v2015, _v2156, _v1966());
                } else {
                    if ((_v319 == _v236)) {
                        bkr_i64 _v355 = _v835(_v554);
                        _v1254 = _v2159(_v1254, _v1546, _v425, _v838(_v554), _v2015, _v2156);
                        _v1254 = _v2159(_v1254, _v1546, _v425, _v841(_v554), _v2015, _v2156);
                        if (_v1965(_v2169, _v355)) {
                            _v1254 = _v2127(_v1254, _v1959(_v425, _v355), _v2015, "for binding", _v2090);
                        }
                        bkr_i64 _v2171 = _v1969(_v2156, _v355);
                        _v1254 = _v2163(_v1254, _v1546, _v425, _v845(_v554), _v2015, _v2171, _v1966());
                    } else {
                        if ((_v319 == _v237)) {
                            _v1254 = _v2163(_v1254, _v1546, _v425, _v847(_v554), _v2015, _v2156, _v1966());
                        } else {
                            if ((_v319 == _v233)) {
                                _v1254 = _v2159(_v1254, _v1546, _v425, _v855(_v554), _v2015, _v2156);
                                _v1254 = _v2159(_v1254, _v1546, _v425, _v858(_v554), _v2015, _v2156);
                            } else {
                                if ((_v319 == _v238)) {
                                    bkr_i64 _v2172 = _v773(_v554);
                                    _v1254 = _v2170(_v1254, _v1546, _v425, _v550(_v2172), _v2015, _v2156, _v2169);
                                } else {
                                    if ((_v319 == _v232)) {
                                        _v1254 = _v2159(_v1254, _v1546, _v425, _v861(_v554), _v2015, _v2156);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1254;
}

bkr_i64 _v2173(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v578, bkr_str _v2015, bkr_i64 _v2174, bkr_i64 _v2175) {
    return _v2163(_v1254, _v477(_v0), _v425, _v580(_v578), _v2015, _v2174, _v2175);
}

bkr_i64 _v2163(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v429 _v583, bkr_str _v2015, bkr_i64 _v2174, bkr_i64 _v2175) {
    bkr_i64 _v2156 = _v1967(_v2174);
    bkr_i64 _v2169 = _v1967(_v2175);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        _v1254 = _v2170(_v1254, _v1546, _v425, _v1111(_v583, _v1172), _v2015, _v2156, _v2169);
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2176(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v558, bkr_str _v2035) {
    return _v2177(_v1254, _v477(_v0), _v425, _v560(_v558), _v2035);
}

bkr_i64 _v2177(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v428 _v563, bkr_str _v2035) {
    bkr_str _v2037 = _v1959(_v425, _v869(_v563));
    bkr_str _v2038 = bkr_str_concat("function:", _v2037);
    _v1254 = _v2153(_v1254, _v1546, _v425, _v875(_v563), _v2038);
    bkr_i64 _v2156 = vec_new();
    bkr_i64 _v2169 = vec_new();
    _v434 _v1145 = _v872(_v563);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1145))) {
        _v341 _v1523 = _v913(_v1145, _v1172);
        bkr_i64 _v355 = _v863(_v1523);
        _v1254 = _v2153(_v1254, _v1546, _v425, _v866(_v1523), _v2038);
        if (_v1965(_v2169, _v355)) {
            _v1254 = _v2127(_v1254, _v1959(_v425, _v355), _v2038, "parameter", _v1523);
        } else {
            vec_push(_v2169, _v355);
        }
        vec_push(_v2156, _v355);
        _v1172 = (_v1172 + 1);
    }
    return _v2163(_v1254, _v1546, _v425, _v877(_v563), _v2038, _v2156, _v2169);
}

bkr_i64 _v2178(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v558) {
    return _v2179(_v1254, _v477(_v0), _v425, _v560(_v558));
}

bkr_i64 _v2179(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v428 _v563) {
    bkr_str _v1697 = _v1959(_v425, _v887(_v563));
    bkr_str _v2039 = bkr_str_concat("struct:", _v1697);
    bkr_i64 _v2169 = vec_new();
    _v434 _v1162 = _v890(_v563);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1162))) {
        _v341 _v1447 = _v913(_v1162, _v1172);
        bkr_i64 _v355 = _v892(_v1447);
        if (_v1965(_v2169, _v355)) {
            _v1254 = _v2127(_v1254, _v1959(_v425, _v355), _v2039, "field", _v1447);
        } else {
            vec_push(_v2169, _v355);
        }
        _v1254 = _v2153(_v1254, _v1546, _v425, _v895(_v1447), _v2039);
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2180(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425) {
    return _v2181(_v1254, _v477(_v0), _v425);
}

bkr_i64 _v2181(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425) {
    bkr_str _v2035 = bkr_str_concat("kernel:", _v1959(_v425, _v664(_v1546)));
    bkr_i64 _v2169 = vec_new();
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        _v341 _v1981 = _v588(_v563);
        bkr_i64 _v319 = _v569(_v563);
        bkr_i64 _v355 = (-1);
        bkr_str _v2126 = "item";
        if ((_v319 == _v224)) {
            _v355 = _v869(_v563);
            _v2126 = "function";
        } else {
            if ((_v319 == _v249)) {
                _v355 = _v879(_v563);
                _v2126 = "constant";
            } else {
                if ((_v319 == _v254)) {
                    _v355 = _v887(_v563);
                    _v2126 = "struct";
                } else {
                    if ((_v319 == _v260)) {
                        _v355 = _v1180(_v563);
                        _v2126 = "type_alias";
                    }
                }
            }
        }
        if ((_v355 >= 0)) {
            if (_v1965(_v2169, _v355)) {
                _v1254 = _v2127(_v1254, _v1959(_v425, _v355), _v2035, _v2126, _v1981);
            } else {
                vec_push(_v2169, _v355);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2182(bkr_i64 _v1254, bkr_i64 _v0) {
    return _v2183(_v1254, _v477(_v0));
}

bkr_i64 _v2183(bkr_i64 _v1254, _v341 _v1546) {
    bkr_i64 _v425 = _v904(_v1546);
    bkr_str _v2035 = bkr_str_concat("kernel:", _v1959(_v425, _v664(_v1546)));
    _v1254 = _v2181(_v1254, _v1546, _v425);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        bkr_i64 _v319 = _v569(_v563);
        if ((_v319 == _v224)) {
            _v1254 = _v2177(_v1254, _v1546, _v425, _v563, _v2035);
        } else {
            if ((_v319 == _v249)) {
                _v1254 = _v2153(_v1254, _v1546, _v425, _v882(_v563), _v2035);
                _v1254 = _v2159(_v1254, _v1546, _v425, _v885(_v563), _v2035, _v1966());
            } else {
                if ((_v319 == _v254)) {
                    _v1254 = _v2179(_v1254, _v1546, _v425, _v563);
                } else {
                    if ((_v319 == _v260)) {
                        _v1254 = _v2153(_v1254, _v1546, _v425, _v1181(_v563), _v2035);
                    }
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_str _v2184(bkr_i64 _v0) {
    bkr_str _v1955 = ",";
    _v341 _v1546 = _v477(_v0);
    bkr_i64 _v1254 = _v1960();
    bkr_bool _v2007 = _v1947(_v1546);
    if (_v2007) {
        _v2183(_v1254, _v1546);
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.self_host.resolver.v1")), _v1955), _v1907("representation", "bootstrap_name_resolver")), _v1955), _v1909("complete", BKR_TRUE)), _v1955), _v1909("truncated", (!_v2007))), _v1955), _v1909("duplicate_detection", BKR_TRUE)), _v1955), _v1909("unresolved_detection", BKR_TRUE)), _v1955), _v1909("visibility_checking", BKR_TRUE)), _v1955), _v1909("import_graph_awareness", BKR_TRUE)), _v1955), _v1909("cross_file_definitions", BKR_TRUE)), _v1955), _v1909("related_declarations", BKR_TRUE)), _v1955), _v1909("structured_repair_metadata", BKR_TRUE)), _v1955), _v1909("diagnostic_phase_field", BKR_TRUE)), _v1955), _v1909("diagnostic_rule_ids", BKR_TRUE)), _v1955), _v1909("diagnostic_severity", BKR_TRUE)), _v1955), _v1909("diagnostic_severity_counts", BKR_TRUE)), _v1955), _v1909("suggested_edit_envelope", BKR_TRUE)), _v1955), _v1909("has_diagnostics", (_v1963(_v1254) > 0))), _v1955), _v1908("diagnostic_count", _v1963(_v1254))), _v1955), _v1908("error_count", _v1963(_v1254))), _v1955), _v1908("warning_count", 0)), _v1955), _v1907("scope_model", "kernel globals plus function/block/pattern binding scopes using interned names with visibility boundaries")), _v1955), _v1907("known_limits", "Resolver validates duplicate declarations, unresolved identifiers, calls, struct types, struct literals, and struct literal fields with related declaration span objects; import visibility boundaries and cross-file definition origins verified.")), _v1955), _v1910("diagnostics", _v1961(_v1254))), "}");
}

bkr_str _v2185(bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_RESOLVER_JSON: ", _v2184(_v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_bool _v2186(bkr_i64 _v319) {
    return ((_v319 == 0) || (_v319 == 1));
}

bkr_bool _v2187(bkr_i64 _v319) {
    return (((_v319 == 0) || (_v319 == 1)) || (_v319 == 2));
}

bkr_bool _v2188(bkr_i64 _v319) {
    return (_v319 == _v316);
}

bkr_bool _v2189(bkr_i64 _v2190, bkr_i64 _v2191) {
    if (((_v2190 == _v316) || (_v2191 == _v316))) {
        return BKR_TRUE;
    }
    if ((_v2191 == _v314)) {
        return BKR_TRUE;
    }
    if ((_v2190 == _v314)) {
        return BKR_FALSE;
    }
    if ((_v2190 == _v2191)) {
        return BKR_TRUE;
    }
    if ((_v2186(_v2190) && _v2186(_v2191))) {
        return BKR_TRUE;
    }
    if ((((((_v2190 == _v310) || (_v2190 == _v311)) || (_v2190 == _v312)) || (_v2190 == _v313)) && ((_v2191 == _v303) || (_v2191 == _v316)))) {
        return BKR_TRUE;
    }
    if ((((((_v2191 == _v310) || (_v2191 == _v311)) || (_v2191 == _v312)) || (_v2191 == _v313)) && ((_v2190 == _v303) || (_v2190 == _v316)))) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2192(bkr_i64 _v319) {
    return ((((_v319 == 0) || (_v319 == 1)) || (_v319 == 2)) || (_v319 == 3));
}

bkr_bool _v2193(bkr_i64 _v319) {
    return (((((((_v319 == _v306) || (_v319 == _v312)) || (_v319 == _v313)) || (_v319 == _v310)) || (_v319 == _v311)) || (_v319 == _v308)) || (_v319 == _v309));
}

bkr_bool _v2194(bkr_i64 _v2195, bkr_i64 _v1803) {
    if (((_v2195 == _v316) || (_v1803 == _v316))) {
        return BKR_TRUE;
    }
    if ((_v2195 == _v1803)) {
        return BKR_TRUE;
    }
    bkr_bool _v2196 = (_v2187(_v2195) || (_v2195 == _v305));
    bkr_bool _v2197 = (_v2187(_v1803) || (_v1803 == _v305));
    if ((_v2196 && _v2197)) {
        return BKR_TRUE;
    }
    bkr_bool _v2198 = _v2193(_v2195);
    bkr_bool _v2199 = _v2193(_v1803);
    if ((((_v2195 == _v303) && _v2199) || (_v2198 && (_v1803 == _v303)))) {
        return BKR_TRUE;
    }
    if ((_v2198 && _v2199)) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2200(bkr_i64 _v2190, bkr_i64 _v2191) {
    if (_v2189(_v2190, _v2191)) {
        return BKR_TRUE;
    }
    if ((_v2192(_v2190) && _v2192(_v2191))) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_i64 _v2201(_v1547 _v2202, bkr_i64 _v1671) {
    if (_v524(_v1671)) {
        return _v316;
    }
    return _v2203(_v2202, _v538(_v1671));
}

bkr_i64 _v2203(_v1547 _v2202, _v426 _v542) {
    return _v1669(_v2202, _v542);
}

bkr_i64 _v2204(bkr_i64 _v516) {
    if (_v524(_v516)) {
        return _v316;
    }
    return _v2205(_v517(_v516));
}

bkr_i64 _v2206(_v341 _v1546, bkr_i64 _v355) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v260)) {
            if ((_v1180(_v563) == _v355)) {
                return _v1181(_v563);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v565();
}

bkr_bool _v2207(_v341 _v1546, bkr_i64 _v355) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v259)) {
            if ((_v1168(_v563) == _v355)) {
                return BKR_TRUE;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2064(_v341 _v1546, _v346 _v521) {
    bkr_i64 _v319 = _v530(_v521);
    if ((_v319 == _v309)) {
        bkr_i64 _v355 = _v532(_v521);
        if (_v2207(_v1546, _v355)) {
            return _v303;
        }
        bkr_i64 _v2208 = _v2206(_v1546, _v355);
        if (_v526(_v2208)) {
            return _v2064(_v1546, _v517(_v2208));
        }
    }
    return _v319;
}

bkr_i64 _v2209(_v341 _v1546, _v428 _v1530) {
    bkr_i64 _v412 = _v875(_v1530);
    if (_v524(_v412)) {
        return _v307;
    }
    return _v2064(_v1546, _v517(_v412));
}

bkr_i64 _v2205(_v346 _v521) {
    return _v530(_v521);
}

bkr_i64 _v2210(bkr_i64 _v930) {
    return _v2211(_v560(_v930));
}

bkr_i64 _v2211(_v428 _v1530) {
    bkr_i64 _v412 = _v875(_v1530);
    if (_v524(_v412)) {
        return _v307;
    }
    return _v2205(_v517(_v412));
}

bkr_str _v2212(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447, bkr_str _v1279, bkr_str _v2213, bkr_str _v2117) {
    return _v2214(_v319, _v1244, _v1363, _v2015, _v477(_v447), _v1279, _v2213, _v2117);
}

bkr_str _v2214(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_str _v1279, bkr_str _v2213, bkr_str _v2117) {
    return _v2215(_v319, _v1244, _v1363, _v2015, _v452, _v1279, _v2213, _v2056(_v316, "expected"), _v2056(_v316, "found"), _v2117);
}

bkr_str _v2215(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_str _v1279, bkr_str _v2213, bkr_str _v2216, bkr_str _v2217, bkr_str _v2117) {
    return _v2218(_v319, _v1244, _v1363, _v2015, _v512(_v452), _v513(_v452), _v1279, _v2213, _v2216, _v2217, _v2117);
}

bkr_str _v2218(bkr_str _v319, bkr_str _v1244, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v1950, bkr_i64 _v1951, bkr_str _v1279, bkr_str _v2213, bkr_str _v2216, bkr_str _v2217, bkr_str _v2117) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("phase", "typecheck")), _v1955), _v1907("kind", _v319)), _v1955), _v1907("rule_id", _v319)), _v1955), _v1907("error_code", _v1244)), _v1955), _v1907("severity", "error")), _v1955), _v1907("name", _v1363)), _v1955), _v1907("scope", _v2015)), _v1955), _v1908("source_start", _v1950)), _v1955), _v1908("source_end", _v1951)), _v1955), _v1909("span_known", ((_v1950 != _v268) && (_v1951 != _v268)))), _v1955), _v1907("expected", _v1279)), _v1955), _v1907("found", _v2213)), _v1955), _v1910("expected_type", _v2216)), _v1955), _v1910("found_type", _v2217)), _v1955), _v1907("suggested_action", _v2117)), _v1955), _v1907("fix_applicability", "manual_review")), _v1955), _v1907("fix_confidence", "medium")), _v1955), _v1909("safe_edit_available", BKR_FALSE)), _v1955), _v1910("suggested_edits", _v1956())), _v1955), _v1907("repair_hint", _v2117)), "}");
}

bkr_i64 _v2219(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117) {
    return _v2220(_v1254, _v319, _v1363, _v2015, _v477(_v447), _v2190, _v2191, _v2117);
}

bkr_i64 _v2220(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117) {
    return _v1964(_v1254, _v2215(_v319, "BKR_SELF_TYPE_MISMATCH", _v1363, _v2015, _v452, _v327(_v2190), _v327(_v2191), _v2056(_v2190, "expected"), _v2056(_v2191, "found"), _v2117));
}

bkr_i64 _v2221(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_i64 _v2222, bkr_i64 _v2223, bkr_str _v2117) {
    return _v1964(_v1254, _v2214(_v319, "BKR_SELF_ARITY_MISMATCH", _v1363, _v2015, _v452, bkr_str_concat(int_to_string(_v2222), " argument(s)"), bkr_str_concat(int_to_string(_v2223), " argument(s)"), _v2117));
}

bkr_i64 _v2224(bkr_i64 _v1254, bkr_str _v2015, _v426 _v1098) {
    bkr_i64 _v1803 = _v545(_v1098);
    bkr_str _v2128 = "Assign only to a mutable local name, an indexed element, or a field access target.";
    return _v1964(_v1254, _v2214("invalid_assignment_target", "BKR_SELF_ASSIGNMENT_TARGET", "assignment", _v2015, _v547(_v1098), "identifier, index, or field access assignment target", _v318(_v1803), _v2128));
}

bkr_i64 _v2225(bkr_i64 _v1254, bkr_str _v2015, _v427 _v554) {
    bkr_str _v2226 = "break";
    if ((_v556(_v554) == _v235)) {
        _v2226 = "continue";
    }
    return _v1964(_v1254, _v2214("invalid_loop_control", "BKR_SELF_CONTROL_FLOW", _v2226, _v2015, _v587(_v554), "inside for, while, or loop", "outside loop", "Move this statement inside a for, while, or loop body."));
}

bkr_i64 _v2227(bkr_i64 _v1254, bkr_i64 _v425, bkr_str _v2015, _v426 _v1098) {
    bkr_str _v2228 = _v1959(_v425, _v663(_v1098));
    return _v1964(_v1254, _v2214("const_assignment", "BKR_SELF_CONST_ASSIGNMENT", _v2228, _v2015, _v547(_v1098), "mutable assignment target", "constant declaration", "Do not assign to a const; introduce a local binding for mutable state."));
}

bkr_i64 _v2229(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v426 _v542) {
    return _v1964(_v1254, _v2214("ambiguous_empty_array", "BKR_SELF_AMBIGUOUS_TYPE", _v1363, _v2015, _v547(_v542), "array element type context", "empty array literal", "Add a type annotation so the empty array element type is known."));
}

bkr_i64 _v2230(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v426 _v542) {
    return _v1964(_v1254, _v2214("ambiguous_none", "BKR_SELF_AMBIGUOUS_TYPE", _v1363, _v2015, _v547(_v542), "Option<T> type context", "None", "Add an Option<T> annotation so the None payload type is known."));
}

bkr_i64 _v2231(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v426 _v542) {
    return _v1964(_v1254, _v2214("ambiguous_result_constructor", "BKR_SELF_AMBIGUOUS_TYPE", _v1363, _v2015, _v547(_v542), "Result<T,E> type context", "result constructor with one unknown side", "Add a Result<T,E> annotation so both Ok and Err payload types are known."));
}

bkr_i64 _v2232(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v426 _v542) {
    return _v1964(_v1254, _v2214("ambiguous_collection_constructor", "BKR_SELF_AMBIGUOUS_TYPE", _v1363, _v2015, _v547(_v542), "collection element/key/value type context", "generic collection constructor", "Add a Vec<T> or HashMap<K,V> annotation so collection types are known."));
}

bkr_i64 _v2233(bkr_i64 _v1254, bkr_str _v1363, bkr_str _v2015, _v426 _v542) {
    return _v1964(_v1254, _v2214("void_value_used", "BKR_SELF_VOID_VALUE", _v1363, _v2015, _v547(_v542), "value-producing expression", "void expression", "Use this call as a standalone statement or change the function to return a value."));
}

bkr_i64 _v2234(bkr_i64 _v1254, bkr_i64 _v425, _v341 _v1546, bkr_str _v2035) {
    bkr_str _v1899 = _v1959(_v425, _v901(_v1546));
    return _v1964(_v1254, _v2214("missing_entry_function", "BKR_SELF_ENTRY_POINT", _v1899, _v2035, _v1546, bkr_str_concat("function named ", _v1899), "missing function declaration", bkr_str_concat(bkr_str_concat("Add fn ", _v1899), "(...) or update the kernel entry name.")));
}

bkr_i64 _v2235(bkr_i64 _v1254, bkr_i64 _v425, bkr_str _v2035, _v428 _v2236, bkr_str _v1279, bkr_str _v2213, bkr_str _v2117) {
    return _v1964(_v1254, _v2214("invalid_entry_signature", "BKR_SELF_ENTRY_POINT", _v1959(_v425, _v869(_v2236)), _v2035, _v588(_v2236), _v1279, _v2213, _v2117));
}

bkr_i64 _v2237(bkr_i64 _v1254, bkr_i64 _v425, bkr_str _v2015, _v426 _v542, bkr_str _v1282) {
    bkr_str _v1764 = _v1959(_v425, _v689(_v542));
    return _v1964(_v1254, _v2214("invalid_call_target", "BKR_SELF_CALL_TARGET", _v1764, _v2015, _v547(_v542), "function or supported builtin", _v1282, "Call only functions and supported builtins; use the symbol as a value or rename it."));
}

bkr_i64 _v2238(bkr_i64 _v1254, bkr_i64 _v425, bkr_str _v2015, _v428 _v1530) {
    return _v1964(_v1254, _v2214("missing_return", "BKR_SELF_RETURN_PATH", _v1959(_v425, _v869(_v1530)), _v2015, _v588(_v1530), "return value on every path", "function can fall through", "Add a return statement on every path or change the function return type to void."));
}

bkr_i64 _v2239(bkr_i64 _v1254, _v1547 _v2202, _v426 _v542, bkr_str _v1363, bkr_str _v2015) {
    if ((_v2203(_v2202, _v542) == _v307)) {
        _v1254 = _v2233(_v1254, _v1363, _v2015, _v542);
    }
    return _v1254;
}

bkr_i64 _v2240(bkr_i64 _v1254, bkr_str _v2015, _v427 _v554) {
    return _v1964(_v1254, _v2214("unreachable_statement", "BKR_SELF_UNREACHABLE_CODE", "statement", _v2015, _v587(_v554), "reachable statement", _v318(_v556(_v554)), "Remove this statement or move it before the terminating control-flow statement."));
}

bkr_bool _v2241(_v426 _v1098) {
    bkr_i64 _v1803 = _v545(_v1098);
    if ((_v1803 == _v245)) {
        return BKR_TRUE;
    }
    if ((_v1803 == _v253)) {
        return BKR_TRUE;
    }
    if ((_v1803 == _v256)) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2242(_v426 _v542) {
    if ((_v545(_v542) != _v252)) {
        return BKR_FALSE;
    }
    return (_v907(_v702(_v542)) == 0);
}

bkr_bool _v2243(bkr_i64 _v1671) {
    if (_v524(_v1671)) {
        return BKR_FALSE;
    }
    return _v2242(_v538(_v1671));
}

bkr_bool _v2244(bkr_i64 _v425, _v426 _v542) {
    if ((_v545(_v542) != _v245)) {
        return BKR_FALSE;
    }
    return bkr_str_eq(_v1959(_v425, _v663(_v542)), "None");
}

bkr_bool _v2245(bkr_i64 _v425, bkr_i64 _v1671) {
    if (_v524(_v1671)) {
        return BKR_FALSE;
    }
    return _v2244(_v425, _v538(_v1671));
}

bkr_bool _v2246(bkr_i64 _v425, _v426 _v542) {
    if ((_v545(_v542) != _v244)) {
        return BKR_FALSE;
    }
    bkr_str _v1656 = _v1959(_v425, _v689(_v542));
    return (((bkr_str_eq(_v1656, "result_ok") || bkr_str_eq(_v1656, "result_err")) || bkr_str_eq(_v1656, "Ok")) || bkr_str_eq(_v1656, "Err"));
}

bkr_bool _v2247(bkr_i64 _v425, bkr_i64 _v1671) {
    if (_v524(_v1671)) {
        return BKR_FALSE;
    }
    return _v2246(_v425, _v538(_v1671));
}

bkr_bool _v2248(bkr_i64 _v425, _v426 _v542) {
    if ((_v545(_v542) != _v244)) {
        return BKR_FALSE;
    }
    bkr_str _v1656 = _v1959(_v425, _v689(_v542));
    return (bkr_str_eq(_v1656, "vec_new") || bkr_str_eq(_v1656, "hashmap_new"));
}

bkr_bool _v2249(bkr_i64 _v425, bkr_i64 _v1671) {
    if (_v524(_v1671)) {
        return BKR_FALSE;
    }
    return _v2248(_v425, _v538(_v1671));
}

bkr_bool _v2250(_v1547 _v2202, bkr_i64 _v1671) {
    if (_v524(_v1671)) {
        return BKR_FALSE;
    }
    return (_v2203(_v2202, _v538(_v1671)) == _v307);
}

bkr_i64 _v2251(bkr_str _v1363) {
    if (bkr_str_eq(_v1363, "print")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "println")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "Some")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "len")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "substr")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "str_eq")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "str_ne")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "str_to_i64")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "i64_to_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "f64_to_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "bool_to_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "read_file")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "write_file")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "file_exists")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "file_set_executable")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "read_file_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "write_file_str")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "vec_new")) {
        return 0;
    }
    if (bkr_str_eq(_v1363, "vec_push")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "vec_get")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "vec_set")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "vec_len")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "vec_pop")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "vec_clear")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "hashmap_new")) {
        return 0;
    }
    if (bkr_str_eq(_v1363, "hashmap_insert")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "hashmap_get")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "hashmap_contains")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "hashmap_remove")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "hashmap_keys")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "hashmap_len")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "hashmap_clear")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "result_ok")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "result_err")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "result_is_ok")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "result_is_err")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "result_unwrap")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "result_unwrap_err")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "result_tag")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "result_value")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "bkr_tuple2")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "bkr_tuple3")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "bkr_tuple_get")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "args_count")) {
        return 0;
    }
    if (bkr_str_eq(_v1363, "arg_at")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "strlen")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "char_code")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "char_code_at")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "char_at")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "substring")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "contains")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "starts_with")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "ends_with")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "trim")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "int_to_string")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "from_char_code")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "join_lines")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "parse_int")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "hashmap_get_opt")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "vec_get_opt")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "vec_pop_opt")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "vec_contains")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "vec_is_empty")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "vec_clone")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "vec_reverse")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "hashmap_is_empty")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "hashmap_values")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "vec_map")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "vec_filter")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "vec_fold")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "vec_find")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "read_file_result")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "write_file_result")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "parse_int_result")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "Ok")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "Err")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "panic")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "assert")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "str_index_of")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "str_replace")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "str_split")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "str_to_upper")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "str_to_lower")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "str_repeat")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "path_join")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "path_dir")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "path_base")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "path_ext")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "path_is_abs")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "env_var")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "env_get")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "env_set")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "env_has")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "time_now_ms")) {
        return 0;
    }
    if (bkr_str_eq(_v1363, "time_now_unix")) {
        return 0;
    }
    if (bkr_str_eq(_v1363, "runtime_version_major")) {
        return 0;
    }
    if (bkr_str_eq(_v1363, "runtime_version_minor")) {
        return 0;
    }
    if (bkr_str_eq(_v1363, "runtime_version_patch")) {
        return 0;
    }
    if (bkr_str_eq(_v1363, "runtime_version_str")) {
        return 0;
    }
    if (bkr_str_eq(_v1363, "bytes_new")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "bytes_len")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "bytes_capacity")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "bytes_get")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "bytes_set")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "bytes_push")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "bytes_from_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "bytes_to_str")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "slice_new")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "slice_len")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "slice_get")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "slice_sub")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "slice_to_vec")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "slice_contains")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "vec_as_slice")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "vec_slice")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "bytes_as_slice")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "bytes_slice")) {
        return 3;
    }
    if (bkr_str_eq(_v1363, "path_exists")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "path_is_file")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "path_is_dir")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "file_read")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "file_write")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "file_size")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "file_remove")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "file_read_bytes")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "file_write_bytes")) {
        return 2;
    }
    if (bkr_str_eq(_v1363, "dir_create")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "dir_remove")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "process_run")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "process_run_status")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "process_exit")) {
        return 1;
    }
    if (bkr_str_eq(_v1363, "process_pid")) {
        return 0;
    }
    if (bkr_str_eq(_v1363, "process_is_sandboxed")) {
        return 0;
    }
    return (-1);
}

bkr_i64 _v2252(bkr_str _v1363, bkr_i64 _v362) {
    if ((bkr_str_eq(_v1363, "print") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "println") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "len") && (_v362 == 0))) {
        return _v316;
    }
    if ((bkr_str_eq(_v1363, "substr") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "substr") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "substr") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "str_eq") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_eq") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_ne") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_ne") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_to_i64") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "i64_to_str") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "f64_to_str") && (_v362 == 0))) {
        return _v304;
    }
    if ((bkr_str_eq(_v1363, "bool_to_str") && (_v362 == 0))) {
        return _v305;
    }
    if ((bkr_str_eq(_v1363, "read_file") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "write_file") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "write_file") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "file_exists") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "file_set_executable") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "read_file_str") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "write_file_str") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "write_file_str") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "vec_push") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_get") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_get") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_set") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_set") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_len") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_pop") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_clear") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "hashmap_insert") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "hashmap_get") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "hashmap_contains") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "hashmap_remove") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "hashmap_keys") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "hashmap_len") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "hashmap_clear") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "result_is_ok") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "result_is_err") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "result_unwrap") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "result_unwrap_err") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "result_tag") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "result_value") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "arg_at") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "strlen") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "char_code") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "char_code_at") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "char_code_at") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "char_at") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "char_at") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "substring") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "substring") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "substring") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "contains") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "contains") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "starts_with") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "starts_with") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "ends_with") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "ends_with") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "trim") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "int_to_string") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "from_char_code") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "parse_int") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "read_file_result") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "write_file_result") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "write_file_result") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "parse_int_result") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "hashmap_get_opt") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_get_opt") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_get_opt") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_pop_opt") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_contains") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_is_empty") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_clone") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_reverse") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "hashmap_is_empty") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "hashmap_values") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_map") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_filter") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_fold") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_find") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "panic") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "assert") && (_v362 == 0))) {
        return _v305;
    }
    if ((bkr_str_eq(_v1363, "str_index_of") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_index_of") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_replace") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_replace") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_replace") && (_v362 == 2))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_split") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_split") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_to_upper") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_to_lower") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_repeat") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "str_repeat") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "path_join") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "path_join") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "path_dir") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "path_base") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "path_ext") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "path_is_abs") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "env_var") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "env_get") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "env_set") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "env_set") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "env_has") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "bytes_new") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_len") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_capacity") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_get") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_get") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_set") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_set") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_set") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_push") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_push") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_from_str") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "bytes_to_str") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_new") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_new") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_new") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_len") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_get") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_get") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_sub") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_sub") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_sub") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_to_vec") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_contains") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "slice_contains") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_as_slice") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_slice") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_slice") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "vec_slice") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_as_slice") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_slice") && (_v362 == 0))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_slice") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "bytes_slice") && (_v362 == 2))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "path_exists") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "path_is_file") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "path_is_dir") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "file_read") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "file_write") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "file_write") && (_v362 == 1))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "file_size") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "file_remove") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "file_read_bytes") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "file_write_bytes") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "file_write_bytes") && (_v362 == 1))) {
        return _v303;
    }
    if ((bkr_str_eq(_v1363, "dir_create") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "dir_remove") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "process_run") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "process_run_status") && (_v362 == 0))) {
        return _v306;
    }
    if ((bkr_str_eq(_v1363, "process_exit") && (_v362 == 0))) {
        return _v303;
    }
    return _v316;
}

bkr_i64 _v2253(bkr_i64 _v1254, bkr_i64 _v425, _v426 _v542, bkr_str _v2015) {
    bkr_str _v2037 = _v1959(_v425, _v689(_v542));
    bkr_i64 _v2222 = _v2251(_v2037);
    if ((_v2222 < 0)) {
        return _v1254;
    }
    bkr_i64 _v2223 = _v907(_v692(_v542));
    if ((_v2222 != _v2223)) {
        bkr_str _v2254 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Call builtin ", _v2037), " with exactly "), int_to_string(_v2222)), " argument(s).");
        _v1254 = _v2221(_v1254, "builtin_argument_count_mismatch", _v2037, _v2015, _v547(_v542), _v2222, _v2223, _v2254);
    }
    return _v1254;
}

bkr_i64 _v2255(bkr_i64 _v1254, bkr_i64 _v425, _v1547 _v2202, _v426 _v542, bkr_str _v2015) {
    bkr_str _v2037 = _v1959(_v425, _v689(_v542));
    if ((_v2251(_v2037) < 0)) {
        return _v1254;
    }
    _v434 _v1016 = _v692(_v542);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1016))) {
        if ((bkr_str_eq(_v2037, "len") && (_v1172 == 0))) {
            _v341 _v2256 = _v913(_v1016, 0);
            bkr_i64 _v2191 = _v2203(_v2202, _v540(_v2256));
            if (((_v2191 != _v306) && (_v2191 != _v308))) {
                bkr_str _v2128 = "Change argument 1 for builtin len to match the expected type.";
                _v1254 = _v2257(_v1254, "builtin_argument_type_mismatch", _v2037, _v2015, _v2256, _v306, _v2191, _v2128);
            }
        } else {
            bkr_i64 _v2190 = _v2252(_v2037, _v1172);
            if ((_v2190 != _v316)) {
                _v341 _v2256 = _v913(_v1016, _v1172);
                bkr_i64 _v2191 = _v2203(_v2202, _v540(_v2256));
                bkr_str _v2128 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Change argument ", int_to_string((_v1172 + 1))), " for builtin "), _v2037), " to match the expected type.");
                _v1254 = _v2257(_v1254, "builtin_argument_type_mismatch", _v2037, _v2015, _v2256, _v2190, _v2191, _v2128);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2258(bkr_i64 _v1254, bkr_i64 _v425, _v1547 _v2202, _v426 _v542, bkr_str _v2015) {
    _v1254 = _v2253(_v1254, _v425, _v542, _v2015);
    _v1254 = _v2255(_v1254, _v425, _v2202, _v542, _v2015);
    return _v1254;
}

bkr_bool _v2259(bkr_i64 _v349) {
    return ((_v349 == _v172) || (_v349 == _v173));
}

bkr_bool _v2260(bkr_i64 _v349) {
    return ((((((_v349 == _v165) || (_v349 == _v175)) || (_v349 == _v176)) || (_v349 == _v177)) || (_v349 == _v178)) || (_v349 == _v179));
}

bkr_bool _v2261(bkr_i64 _v349) {
    return ((((((((_v349 == _v161) || (_v349 == _v162)) || (_v349 == _v163)) || (_v349 == _v164)) || (_v349 == _v168)) || (_v349 == _v169)) || (_v349 == _v170)) || (_v349 == _v171));
}

bkr_i64 _v2262(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117) {
    return _v2257(_v1254, _v319, _v1363, _v2015, _v477(_v447), _v2190, _v2191, _v2117);
}

bkr_i64 _v2257(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117) {
    if ((!_v2189(_v2190, _v2191))) {
        _v1254 = _v2220(_v1254, _v319, _v1363, _v2015, _v452, _v2190, _v2191, _v2117);
    }
    return _v1254;
}

bkr_i64 _v2263(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, bkr_i64 _v447, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117) {
    return _v2264(_v1254, _v319, _v1363, _v2015, _v477(_v447), _v2190, _v2191, _v2117);
}

bkr_i64 _v2264(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v341 _v452, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117) {
    if ((!_v2200(_v2190, _v2191))) {
        _v1254 = _v2220(_v1254, _v319, _v1363, _v2015, _v452, _v2190, _v2191, _v2117);
    }
    return _v1254;
}

_v428 _v2265(_v341 _v1546, bkr_i64 _v355) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v224) && (_v869(_v563) == _v355))) {
            return _v563;
        }
        _v1172 = (_v1172 + 1);
    }
    return _v564();
}

bkr_i64 _v2266(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, bkr_str _v2035) {
    _v428 _v2236 = _v2265(_v1546, _v901(_v1546));
    if (_v566(_v2236)) {
        _v1254 = _v2234(_v1254, _v425, _v1546, _v2035);
        return _v1254;
    }
    _v434 _v1145 = _v872(_v2236);
    bkr_i64 _v2267 = _v907(_v1145);
    if ((_v2267 != 0)) {
        _v1254 = _v2235(_v1254, _v425, _v2035, _v2236, "entry function with zero parameters", bkr_str_concat(int_to_string(_v2267), " parameter(s)"), "Remove entry function parameters or make a zero-argument wrapper entry.");
    }
    bkr_i64 _v2268 = _v2209(_v1546, _v2236);
    if (((_v2268 != _v316) && (!_v2186(_v2268)))) {
        _v1254 = _v2235(_v1254, _v425, _v2035, _v2236, "integer-compatible entry return type", _v327(_v2268), "Return i32 or i64 from the entry function so the generated C main can return an int.");
    }
    return _v1254;
}

bkr_i64 _v2269(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v426 _v542, bkr_str _v2015) {
    bkr_i64 _v355 = _v689(_v542);
    if (_v567(_v2265(_v1546, _v355))) {
        return _v1254;
    }
    if (_v567(_v2270(_v1546, _v355))) {
        return _v2237(_v1254, _v425, _v2015, _v542, "constant declaration");
    }
    _v428 _v1539 = _v2271(_v1546, _v355);
    if (_v567(_v1539)) {
        _v434 _v1162 = _v890(_v1539);
        if ((_v907(_v1162) > 0)) {
            _v341 _v2272 = _v913(_v1162, 0);
            if (bkr_str_eq(_v1959(_v425, _v892(_v2272)), "0")) {
                return _v1254;
            }
        }
        return _v2237(_v1254, _v425, _v2015, _v542, "struct declaration");
    }
    return _v1254;
}

_v428 _v2271(_v341 _v1546, bkr_i64 _v355) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v254) && (_v887(_v563) == _v355))) {
            return _v563;
        }
        _v1172 = (_v1172 + 1);
    }
    return _v564();
}

_v428 _v2270(_v341 _v1546, bkr_i64 _v355) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v249) && (_v879(_v563) == _v355))) {
            return _v563;
        }
        _v1172 = (_v1172 + 1);
    }
    return _v564();
}

bkr_i64 _v2273(_v341 _v1546, bkr_i64 _v1519, bkr_i64 _v1674) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v254) && (_v887(_v563) == _v1519))) {
            _v434 _v1162 = _v890(_v563);
            bkr_i64 _v1645 = 0;
            while ((_v1645 < _v907(_v1162))) {
                _v341 _v1447 = _v913(_v1162, _v1645);
                if ((_v892(_v1447) == _v1674)) {
                    return _v2064(_v1546, _v517(_v895(_v1447)));
                }
                _v1645 = (_v1645 + 1);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v316;
}

bkr_i64 _v2274(bkr_i64 _v1254, bkr_i64 _v425, _v426 _v542, bkr_str _v2015) {
    bkr_str _v1697 = _v1959(_v425, _v725(_v542));
    _v435 _v1008 = _v728(_v542);
    _v434 _v1009 = _v731(_v542);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v916(_v1008))) {
        bkr_i64 _v1674 = _v918(_v1008, _v1172);
        bkr_i64 _v1645 = 0;
        while ((_v1645 < _v1172)) {
            if ((_v918(_v1008, _v1645) == _v1674)) {
                bkr_str _v1045 = _v1959(_v425, _v1674);
                _v1254 = _v1964(_v1254, _v2214("duplicate_struct_literal_field", "BKR_SELF_STRUCT_LITERAL", bkr_str_concat(bkr_str_concat(_v1697, "."), _v1045), _v2015, _v913(_v1009, _v1172), "field initialized once", "duplicate field initializer", "Remove the duplicate field or merge the intended value into the first initializer."));
            }
            _v1645 = (_v1645 + 1);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_bool _v2275(_v435 _v1008, bkr_i64 _v1674) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v916(_v1008))) {
        if ((_v918(_v1008, _v1172) == _v1674)) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2276(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v426 _v542, bkr_str _v2015) {
    bkr_i64 _v403 = _v1006(_v542);
    if ((_v403 != 0)) {
        return _v1254;
    }
    bkr_i64 _v1519 = _v725(_v542);
    _v428 _v1539 = _v2271(_v1546, _v1519);
    if (_v566(_v1539)) {
        return _v1254;
    }
    bkr_str _v1697 = _v1959(_v425, _v1519);
    _v435 _v1008 = _v728(_v542);
    _v434 _v2277 = _v890(_v1539);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v2277))) {
        _v341 _v1447 = _v913(_v2277, _v1172);
        bkr_i64 _v1674 = _v892(_v1447);
        if ((!_v2275(_v1008, _v1674))) {
            bkr_str _v1045 = _v1959(_v425, _v1674);
            _v1254 = _v1964(_v1254, _v2214("missing_struct_literal_field", "BKR_SELF_STRUCT_LITERAL", bkr_str_concat(bkr_str_concat(_v1697, "."), _v1045), _v2015, _v547(_v542), "field initializer", "missing field", bkr_str_concat(bkr_str_concat("Add an initializer for ", _v1045), " or update the struct definition.")));
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2278(bkr_i64 _v1254, bkr_str _v2015, bkr_str _v2279, _v426 _v1032, bkr_i64 _v2190, bkr_i64 _v2191, bkr_str _v2117) {
    if (_v2188(_v2191)) {
        return _v1254;
    }
    return _v2220(_v1254, "binary_operand_type_mismatch", _v2279, _v2015, _v547(_v1032), _v2190, _v2191, _v2117);
}

bkr_i64 _v2280(bkr_i64 _v1254, _v1547 _v2202, _v426 _v542, bkr_str _v2015) {
    bkr_i64 _v349 = _v672(_v542);
    _v426 _v1051 = _v538(_v675(_v542));
    _v426 _v1052 = _v538(_v678(_v542));
    bkr_i64 _v1691 = _v2203(_v2202, _v1051);
    bkr_i64 _v1692 = _v2203(_v2202, _v1052);
    bkr_str _v2281 = _v1321(_v349);
    if (_v2259(_v349)) {
        if ((_v1691 != _v305)) {
            _v1254 = _v2278(_v1254, _v2015, bkr_str_concat("left operand for ", _v2281), _v1051, _v305, _v1691, bkr_str_concat(bkr_str_concat("Use bool operands with ", _v2281), "."));
        }
        if ((_v1692 != _v305)) {
            _v1254 = _v2278(_v1254, _v2015, bkr_str_concat("right operand for ", _v2281), _v1052, _v305, _v1692, bkr_str_concat(bkr_str_concat("Use bool operands with ", _v2281), "."));
        }
    } else {
        if (_v2260(_v349)) {
            if ((!_v2186(_v1691))) {
                _v1254 = _v2278(_v1254, _v2015, bkr_str_concat("left operand for ", _v2281), _v1051, _v303, _v1691, bkr_str_concat(bkr_str_concat("Use integer operands with ", _v2281), "."));
            }
            if ((!_v2186(_v1692))) {
                _v1254 = _v2278(_v1254, _v2015, bkr_str_concat("right operand for ", _v2281), _v1052, _v303, _v1692, bkr_str_concat(bkr_str_concat("Use integer operands with ", _v2281), "."));
            }
        } else {
            if (_v2261(_v349)) {
                if (((_v349 == _v161) && ((_v1691 == _v306) || (_v1692 == _v306)))) {
                    return _v1254;
                }
                if ((!_v2187(_v1691))) {
                    _v1254 = _v2278(_v1254, _v2015, bkr_str_concat("left operand for ", _v2281), _v1051, _v303, _v1691, bkr_str_concat(bkr_str_concat("Use numeric operands with ", _v2281), "."));
                }
                if ((!_v2187(_v1692))) {
                    _v1254 = _v2278(_v1254, _v2015, bkr_str_concat("right operand for ", _v2281), _v1052, _v303, _v1692, bkr_str_concat(bkr_str_concat("Use numeric operands with ", _v2281), "."));
                }
            } else {
                if (((_v349 == _v166) || (_v349 == _v167))) {
                    if ((!_v2189(_v1691, _v1692))) {
                        _v1254 = _v2220(_v1254, "binary_operand_type_mismatch", bkr_str_concat("right operand for ", _v2281), _v2015, _v547(_v1052), _v1691, _v1692, "Compare values with compatible operand types.");
                    }
                }
            }
        }
    }
    return _v1254;
}

bkr_bool _v2282(_v1547 _v2202, _v426 _v542) {
    if ((_v545(_v542) != _v242)) {
        return BKR_FALSE;
    }
    if ((_v672(_v542) != _v176)) {
        return BKR_FALSE;
    }
    _v426 _v1052 = _v538(_v678(_v542));
    if ((_v545(_v1052) != _v256)) {
        return BKR_FALSE;
    }
    _v426 _v1038 = _v538(_v720(_v1052));
    if ((_v545(_v1038) != _v245)) {
        return BKR_FALSE;
    }
    bkr_i64 _v425 = _v1577(_v2202);
    bkr_str _v1642 = _v1641(_v425, _v663(_v1038));
    bkr_str _v1644 = _v1641(_v425, _v723(_v1052));
    bkr_i64 _v1690 = _v1643(_v2202, _v1642, _v1644);
    return (_v1690 >= 0);
}

bkr_i64 _v2283(bkr_i64 _v1254, _v1547 _v2202, _v426 _v542, bkr_str _v2015) {
    bkr_i64 _v349 = _v682(_v542);
    _v426 _v1032 = _v538(_v685(_v542));
    bkr_i64 _v2284 = _v2203(_v2202, _v1032);
    if (_v2188(_v2284)) {
        return _v1254;
    }
    if (((_v349 == _v174) && (_v2284 != _v305))) {
        return _v2220(_v1254, "unary_operand_type_mismatch", "operand for !", _v2015, _v547(_v1032), _v305, _v2284, "Use a bool operand with !.");
    }
    if (((_v349 == _v162) && (!_v2187(_v2284)))) {
        return _v2220(_v1254, "unary_operand_type_mismatch", "operand for unary -", _v2015, _v547(_v1032), _v303, _v2284, "Use a numeric operand with unary -.");
    }
    return _v1254;
}

bkr_i64 _v2285(bkr_i64 _v1254, _v1547 _v2202, _v426 _v542, bkr_str _v2015) {
    bkr_i64 _v1045 = _v723(_v542);
    bkr_i64 _v425 = _v1577(_v2202);
    bkr_str _v1783 = _v1641(_v425, _v1045);
    if ((((bkr_str_eq(_v1783, "0") || bkr_str_eq(_v1783, "1")) || bkr_str_eq(_v1783, "2")) || bkr_str_eq(_v1783, "3"))) {
        return _v1254;
    }
    _v426 _v1038 = _v538(_v720(_v542));
    if ((_v545(_v1038) == _v245)) {
        bkr_str _v1642 = _v1641(_v425, _v663(_v1038));
        bkr_i64 _v1690 = _v1643(_v2202, _v1642, _v1783);
        if ((_v1690 >= 0)) {
            return _v1254;
        }
    }
    bkr_i64 _v2286 = _v2203(_v2202, _v1038);
    if ((_v2286 == _v316)) {
        return _v1254;
    }
    if ((_v2286 != _v309)) {
        _v1254 = _v2220(_v1254, "field_access_base_type_mismatch", "field access base", _v2015, _v547(_v1038), _v309, _v2286, "Access fields only on struct values.");
    }
    return _v1254;
}

bkr_i64 _v2287(bkr_i64 _v1254, _v1547 _v2202, _v426 _v542, bkr_str _v2015) {
    _v426 _v1038 = _v538(_v712(_v542));
    bkr_i64 _v2286 = _v2203(_v2202, _v1038);
    if ((_v2286 == _v316)) {
        return _v1254;
    }
    if ((_v2286 != _v308)) {
        _v1254 = _v2220(_v1254, "index_base_type_mismatch", "index base", _v2015, _v547(_v1038), _v308, _v2286, "Index only array values; use Vec/HashMap builtins for handle collections.");
    }
    return _v1254;
}

bkr_i64 _v2288(_v1547 _v2202, _v341 _v1127) {
    if ((_v510(_v1127) == _v227)) {
        _v429 _v583 = _v581(_v1127);
        if ((_v590(_v583) <= 0)) {
            return _v316;
        }
        _v427 _v1687 = _v1111(_v583, (_v590(_v583) - 1));
        if ((_v556(_v1687) == _v232)) {
            return _v2203(_v2202, _v538(_v861(_v1687)));
        }
        return _v316;
    }
    return _v2203(_v2202, _v540(_v1127));
}

bkr_i64 _v2289(bkr_i64 _v1254, _v1547 _v2202, _v434 _v976, bkr_str _v2015) {
    if ((_v907(_v976) <= 1)) {
        return _v1254;
    }
    _v341 _v2290 = _v913(_v976, 0);
    bkr_i64 _v2190 = _v2288(_v2202, _v2290);
    bkr_i64 _v1172 = 1;
    while ((_v1172 < _v907(_v976))) {
        _v341 _v1127 = _v913(_v976, _v1172);
        bkr_i64 _v2191 = _v2288(_v2202, _v1127);
        _v1254 = _v2264(_v1254, "match_arm_type_mismatch", bkr_str_concat("match arm ", int_to_string((_v1172 + 1))), _v2015, _v1127, _v2190, _v2191, "Make every match arm produce a compatible value type.");
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2291(_v433 _v473) {
    bkr_i64 _v2292 = _v597(_v473);
    if ((_v2292 == _v292)) {
        return _v303;
    }
    if ((_v2292 == _v293)) {
        return _v309;
    }
    if ((_v2292 == _v283)) {
        return _v303;
    }
    if ((_v2292 == _v284)) {
        return _v305;
    }
    if (((_v2292 == _v287) || (_v2292 == _v288))) {
        return _v312;
    }
    if (((_v2292 == _v290) || (_v2292 == _v291))) {
        return _v313;
    }
    return _v316;
}

bkr_bool _v2293(bkr_i64 _v1731, bkr_i64 _v2190) {
    if (((_v1731 == _v316) || (_v2190 == _v316))) {
        return BKR_TRUE;
    }
    if ((_v1731 == _v2190)) {
        return BKR_TRUE;
    }
    if ((_v2186(_v1731) && _v2186(_v2190))) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_i64 _v2294(bkr_i64 _v1254, _v436 _v621, bkr_i64 _v1731, bkr_str _v2015) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        _v433 _v473 = _v925(_v621, _v1172);
        bkr_i64 _v2190 = _v2291(_v473);
        if (((_v2190 != _v316) && (!_v2293(_v1731, _v2190)))) {
            _v1254 = _v1964(_v1254, _v2218("match_pattern_type_mismatch", "BKR_SELF_TYPE_MISMATCH", bkr_str_concat("match pattern ", int_to_string((_v1172 + 1))), _v2015, _v602(_v473), _v603(_v473), _v327(_v1731), _v327(_v2190), _v2056(_v1731, "expected"), _v2056(_v2190, "found"), "Use a pattern that matches the scrutinee type."));
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_bool _v2295(_v433 _v473) {
    bkr_i64 _v319 = _v597(_v473);
    return (((_v319 == _v283) || (_v319 == _v284)) || (_v319 == _v288));
}

bkr_bool _v2296(_v433 _v473) {
    bkr_i64 _v319 = _v597(_v473);
    if ((((_v319 == _v286) || (_v319 == _v285)) || (_v319 == _v293))) {
        return BKR_TRUE;
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            bkr_i64 _v1390 = ((bkr_i64)(_v345));
            bkr_i64 _v1172 = 0;
            while ((_v1172 < vec_len(_v1390))) {
                _v433 _v1408 = _v592(vec_get(_v1390, _v1172));
                if ((!_v2296(_v1408))) {
                    return BKR_FALSE;
                }
                _v1172 = (_v1172 + 1);
            }
            return BKR_TRUE;
        }
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2297(_v433 _v1051, _v433 _v1052) {
    if ((_v597(_v1051) != _v597(_v1052))) {
        return BKR_FALSE;
    }
    bkr_i64 _v319 = _v597(_v1051);
    if ((((_v597(_v1051) == _v287) || (_v319 == _v290)) || (_v319 == _v291))) {
        bkr_i64 _v2298 = _v599(_v1051);
        bkr_i64 _v2299 = _v599(_v1052);
        if (((_v2298 != 0) || (_v2299 != 0))) {
            if (((_v2298 != 0) && (_v2299 != 0))) {
                _v433 _v2300 = _v592(_v2298);
                _v433 _v2301 = _v592(_v2299);
                return _v2297(_v2300, _v2301);
            }
            return BKR_FALSE;
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v292)) {
        bkr_i64 _v2298 = _v599(_v1051);
        bkr_i64 _v2299 = _v599(_v1052);
        if (((_v2298 != 0) && (_v2299 != 0))) {
            bkr_i64 _v2302 = ((bkr_i64)(_v2298));
            bkr_i64 _v2303 = ((bkr_i64)(_v2299));
            if ((vec_len(_v2302) != vec_len(_v2303))) {
                return BKR_FALSE;
            }
            bkr_i64 _v1172 = 0;
            while ((_v1172 < vec_len(_v2302))) {
                _v433 _v2304 = _v592(vec_get(_v2302, _v1172));
                _v433 _v2305 = _v592(vec_get(_v2303, _v1172));
                if ((!_v2297(_v2304, _v2305))) {
                    return BKR_FALSE;
                }
                _v1172 = (_v1172 + 1);
            }
            return BKR_TRUE;
        }
        return BKR_FALSE;
    }
    if ((!_v2295(_v1051))) {
        return BKR_FALSE;
    }
    return (_v598(_v1051) == _v598(_v1052));
}

bkr_i64 _v2306(bkr_i64 _v1254, bkr_str _v319, bkr_str _v1363, bkr_str _v2015, _v433 _v473, bkr_str _v1279, bkr_str _v2213, bkr_str _v2117) {
    return _v1964(_v1254, _v2218(_v319, "BKR_SELF_MATCH_PATTERN", _v1363, _v2015, _v602(_v473), _v603(_v473), _v1279, _v2213, _v2056(_v316, "expected"), _v2056(_v316, "found"), _v2117));
}

bkr_i64 _v2307(bkr_i64 _v1254, _v435 _v977, _v436 _v621, bkr_str _v2015) {
    bkr_bool _v2308 = BKR_FALSE;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        bkr_bool _v2309 = ((_v1172 < _v916(_v977)) && (_v918(_v977, _v1172) != 0));
        _v433 _v473 = _v925(_v621, _v1172);
        if (_v2308) {
            _v1254 = _v2306(_v1254, "unreachable_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1172 + 1))), _v2015, _v473, "reachable match pattern", "previous catch-all pattern already matches", "Remove this arm or move it before the catch-all pattern.");
        } else {
            if ((!_v2309)) {
                bkr_i64 _v1645 = 0;
                while ((_v1645 < _v1172)) {
                    bkr_bool _v2310 = ((_v1645 < _v916(_v977)) && (_v918(_v977, _v1645) != 0));
                    if ((!_v2310)) {
                        _v433 _v2311 = _v925(_v621, _v1645);
                        if (_v2297(_v2311, _v473)) {
                            _v1254 = _v2306(_v1254, "duplicate_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1172 + 1))), _v2015, _v473, "unique match pattern", _v328(_v597(_v473)), "Remove the duplicate pattern or merge its arm with the first occurrence.");
                        }
                    }
                    _v1645 = (_v1645 + 1);
                }
                if (_v2296(_v473)) {
                    _v2308 = BKR_TRUE;
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_bool _v2312(_v435 _v977, _v436 _v621, bkr_i64 _v387) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        if (((_v1172 < _v916(_v977)) && (_v918(_v977, _v1172) != 0))) {
            _v1172 = (_v1172 + 1);
            continue;
        }
        _v433 _v473 = _v925(_v621, _v1172);
        if (_v2296(_v473)) {
            return BKR_TRUE;
        }
        if (((_v597(_v473) == _v284) && (_v598(_v473) == _v387))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2314(_v436 _v621) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        bkr_i64 _v2292 = _v597(_v925(_v621, _v1172));
        if (((_v2292 == _v287) || (_v2292 == _v288))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2315(bkr_i64 _v2316) {
    bkr_i64 _v1172 = 0;
    bkr_bool _v2317 = BKR_FALSE;
    bkr_bool _v2318 = BKR_FALSE;
    bkr_bool _v2319 = BKR_FALSE;
    bkr_bool _v2320 = BKR_FALSE;
    bkr_bool _v2321 = BKR_FALSE;
    bkr_bool _v2322 = BKR_FALSE;
    while ((_v1172 < vec_len(_v2316))) {
        _v433 _v2323 = _v592(vec_get(_v2316, _v1172));
        if (_v2296(_v2323)) {
            return BKR_TRUE;
        }
        bkr_i64 _v319 = _v597(_v2323);
        if ((_v319 == _v287)) {
            bkr_i64 _v345 = _v599(_v2323);
            if ((_v345 == 0)) {
                _v2317 = BKR_TRUE;
            } else {
                _v433 _v2324 = _v592(_v345);
                if (_v2296(_v2324)) {
                    _v2317 = BKR_TRUE;
                }
            }
        }
        if ((_v319 == _v288)) {
            _v2318 = BKR_TRUE;
        }
        if ((_v319 == _v290)) {
            bkr_i64 _v345 = _v599(_v2323);
            if ((_v345 == 0)) {
                _v2319 = BKR_TRUE;
            } else {
                _v433 _v2324 = _v592(_v345);
                if (_v2296(_v2324)) {
                    _v2319 = BKR_TRUE;
                }
            }
        }
        if ((_v319 == _v291)) {
            bkr_i64 _v345 = _v599(_v2323);
            if ((_v345 == 0)) {
                _v2320 = BKR_TRUE;
            } else {
                _v433 _v2324 = _v592(_v345);
                if (_v2296(_v2324)) {
                    _v2320 = BKR_TRUE;
                }
            }
        }
        if ((_v319 == _v284)) {
            if ((_v598(_v2323) == 1)) {
                _v2321 = BKR_TRUE;
            }
            if ((_v598(_v2323) == 0)) {
                _v2322 = BKR_TRUE;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    if ((_v2317 && _v2318)) {
        return BKR_TRUE;
    }
    if ((_v2319 && _v2320)) {
        return BKR_TRUE;
    }
    if ((_v2321 && _v2322)) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2325(_v435 _v977, _v436 _v621, bkr_i64 _v2292) {
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2316 = vec_new();
    while ((_v1172 < _v920(_v621))) {
        if (((_v1172 < _v916(_v977)) && (_v918(_v977, _v1172) != 0))) {
            _v1172 = (_v1172 + 1);
            continue;
        }
        _v433 _v473 = _v925(_v621, _v1172);
        if (_v2296(_v473)) {
            return BKR_TRUE;
        }
        if ((_v597(_v473) == _v2292)) {
            if ((_v2292 == _v287)) {
                bkr_i64 _v345 = _v599(_v473);
                if ((_v345 == 0)) {
                    return BKR_TRUE;
                }
                _v433 _v1408 = _v592(_v345);
                if (_v2296(_v1408)) {
                    return BKR_TRUE;
                }
                vec_push(_v2316, _v345);
            } else {
                return BKR_TRUE;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    if (((_v2292 == _v287) && (vec_len(_v2316) > 0))) {
        return _v2315(_v2316);
    }
    return BKR_FALSE;
}

bkr_i64 _v2326(bkr_i64 _v1254, _v426 _v542, _v436 _v621, bkr_i64 _v1731, bkr_str _v2015) {
    if ((_v1731 != _v305)) {
        return _v1254;
    }
    _v435 _v977 = _v751(_v542);
    bkr_bool _v2327 = _v2312(_v977, _v621, 1);
    bkr_bool _v2328 = _v2312(_v977, _v621, 0);
    if ((_v2327 && _v2328)) {
        return _v1254;
    }
    bkr_str _v2329 = "";
    if ((!_v2327)) {
        _v2329 = "true";
    }
    if ((!_v2328)) {
        if ((bkr_len((bkr_str)(intptr_t)(_v2329)) > 0)) {
            _v2329 = bkr_str_concat(_v2329, ", false");
        } else {
            _v2329 = "false";
        }
    }
    return _v1964(_v1254, _v2214("non_exhaustive_match", "BKR_SELF_EXHAUSTIVENESS", "match", _v2015, _v547(_v542), "patterns covering true and false", bkr_str_concat("missing ", _v2329), "Add the missing boolean pattern arm or a catch-all pattern."));
}

bkr_i64 _v2330(bkr_i64 _v1254, _v435 _v977, _v436 _v621, bkr_i64 _v1731, bkr_str _v2015) {
    if ((_v1731 != _v305)) {
        return _v1254;
    }
    bkr_bool _v2327 = BKR_FALSE;
    bkr_bool _v2328 = BKR_FALSE;
    bkr_bool _v2331 = BKR_FALSE;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        bkr_bool _v2309 = ((_v1172 < _v916(_v977)) && (_v918(_v977, _v1172) != 0));
        _v433 _v473 = _v925(_v621, _v1172);
        if (_v2331) {
            _v1254 = _v2306(_v1254, "unreachable_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1172 + 1))), _v2015, _v473, "reachable match pattern", "previous bool patterns already cover true and false", "Remove this arm or move it before the exhaustive bool patterns.");
        }
        if ((!_v2309)) {
            if (((_v597(_v473) == _v284) && (_v598(_v473) == 1))) {
                _v2327 = BKR_TRUE;
            }
            if (((_v597(_v473) == _v284) && (_v598(_v473) == 0))) {
                _v2328 = BKR_TRUE;
            }
            if ((_v2327 && _v2328)) {
                _v2331 = BKR_TRUE;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2332(bkr_i64 _v1254, _v426 _v542, _v436 _v621, bkr_str _v2015) {
    if ((!_v2314(_v621))) {
        return _v1254;
    }
    _v435 _v977 = _v751(_v542);
    bkr_bool _v2333 = _v2325(_v977, _v621, _v287);
    bkr_bool _v2334 = _v2325(_v977, _v621, _v288);
    if ((_v2333 && _v2334)) {
        return _v1254;
    }
    bkr_str _v2329 = "";
    if ((!_v2333)) {
        _v2329 = "Some";
    }
    if ((!_v2334)) {
        if ((bkr_len((bkr_str)(intptr_t)(_v2329)) > 0)) {
            _v2329 = bkr_str_concat(_v2329, ", None");
        } else {
            _v2329 = "None";
        }
    }
    return _v1964(_v1254, _v2214("non_exhaustive_match", "BKR_SELF_EXHAUSTIVENESS", "match", _v2015, _v547(_v542), "patterns covering Some and None", bkr_str_concat("missing ", _v2329), "Add the missing Option pattern arm or a catch-all pattern."));
}

bkr_i64 _v2335(bkr_i64 _v1254, _v435 _v977, _v436 _v621, bkr_str _v2015) {
    if ((!_v2314(_v621))) {
        return _v1254;
    }
    bkr_bool _v2333 = BKR_FALSE;
    bkr_bool _v2334 = BKR_FALSE;
    bkr_bool _v2331 = BKR_FALSE;
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2316 = vec_new();
    while ((_v1172 < _v920(_v621))) {
        bkr_bool _v2309 = ((_v1172 < _v916(_v977)) && (_v918(_v977, _v1172) != 0));
        _v433 _v473 = _v925(_v621, _v1172);
        if (_v2331) {
            _v1254 = _v2306(_v1254, "unreachable_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1172 + 1))), _v2015, _v473, "reachable match pattern", "previous Option patterns already cover Some and None", "Remove this arm or move it before the exhaustive Option patterns.");
        }
        if ((!_v2309)) {
            if ((_v597(_v473) == _v287)) {
                bkr_i64 _v345 = _v599(_v473);
                if ((_v345 == 0)) {
                    _v2333 = BKR_TRUE;
                } else {
                    _v433 _v1408 = _v592(_v345);
                    if (_v2296(_v1408)) {
                        _v2333 = BKR_TRUE;
                    } else {
                        vec_push(_v2316, _v345);
                        if (_v2315(_v2316)) {
                            _v2333 = BKR_TRUE;
                        }
                    }
                }
            }
            if ((_v597(_v473) == _v288)) {
                _v2334 = BKR_TRUE;
            }
            if ((_v2333 && _v2334)) {
                _v2331 = BKR_TRUE;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_bool _v2336(_v436 _v621) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        _v433 _v473 = _v925(_v621, _v1172);
        bkr_i64 _v319 = _v597(_v473);
        if (((_v319 == _v290) || (_v319 == _v291))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2337(_v435 _v977, _v436 _v621, bkr_i64 _v2292) {
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2316 = vec_new();
    while ((_v1172 < _v920(_v621))) {
        if (((_v1172 < _v916(_v977)) && (_v918(_v977, _v1172) != 0))) {
            _v1172 = (_v1172 + 1);
            continue;
        }
        _v433 _v473 = _v925(_v621, _v1172);
        if (_v2296(_v473)) {
            return BKR_TRUE;
        }
        if ((_v597(_v473) == _v2292)) {
            bkr_i64 _v345 = _v599(_v473);
            if ((_v345 == 0)) {
                return BKR_TRUE;
            }
            _v433 _v1408 = _v592(_v345);
            if (_v2296(_v1408)) {
                return BKR_TRUE;
            }
            vec_push(_v2316, _v345);
        }
        _v1172 = (_v1172 + 1);
    }
    if ((vec_len(_v2316) > 0)) {
        return _v2315(_v2316);
    }
    return BKR_FALSE;
}

bkr_i64 _v2338(bkr_i64 _v1254, _v426 _v542, _v436 _v621, bkr_str _v2015) {
    if ((!_v2336(_v621))) {
        return _v1254;
    }
    _v435 _v977 = _v751(_v542);
    bkr_bool _v2339 = _v2337(_v977, _v621, _v290);
    bkr_bool _v2340 = _v2337(_v977, _v621, _v291);
    if ((_v2339 && _v2340)) {
        return _v1254;
    }
    bkr_str _v2329 = "";
    if ((!_v2339)) {
        _v2329 = "Ok";
    }
    if ((!_v2340)) {
        if ((bkr_len((bkr_str)(intptr_t)(_v2329)) > 0)) {
            _v2329 = bkr_str_concat(_v2329, ", Err");
        } else {
            _v2329 = "Err";
        }
    }
    return _v1964(_v1254, _v2214("non_exhaustive_match", "BKR_SELF_EXHAUSTIVENESS", "match", _v2015, _v547(_v542), "patterns covering Ok and Err", bkr_str_concat("missing ", _v2329), "Add the missing Result pattern arm or a catch-all pattern."));
}

bkr_i64 _v2341(bkr_i64 _v1254, _v435 _v977, _v436 _v621, bkr_str _v2015) {
    if ((!_v2336(_v621))) {
        return _v1254;
    }
    bkr_bool _v2339 = BKR_FALSE;
    bkr_bool _v2340 = BKR_FALSE;
    bkr_bool _v2331 = BKR_FALSE;
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2342 = vec_new();
    bkr_i64 _v2343 = vec_new();
    while ((_v1172 < _v920(_v621))) {
        bkr_bool _v2309 = ((_v1172 < _v916(_v977)) && (_v918(_v977, _v1172) != 0));
        _v433 _v473 = _v925(_v621, _v1172);
        if (_v2331) {
            _v1254 = _v2306(_v1254, "unreachable_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1172 + 1))), _v2015, _v473, "reachable match pattern", "previous Result patterns already cover Ok and Err", "Remove this arm or move it before the exhaustive Result patterns.");
        }
        if ((!_v2309)) {
            if ((_v597(_v473) == _v290)) {
                bkr_i64 _v345 = _v599(_v473);
                if ((_v345 == 0)) {
                    _v2339 = BKR_TRUE;
                } else {
                    _v433 _v1408 = _v592(_v345);
                    if (_v2296(_v1408)) {
                        _v2339 = BKR_TRUE;
                    } else {
                        vec_push(_v2342, _v345);
                        if (_v2315(_v2342)) {
                            _v2339 = BKR_TRUE;
                        }
                    }
                }
            }
            if ((_v597(_v473) == _v291)) {
                bkr_i64 _v345 = _v599(_v473);
                if ((_v345 == 0)) {
                    _v2340 = BKR_TRUE;
                } else {
                    _v433 _v1408 = _v592(_v345);
                    if (_v2296(_v1408)) {
                        _v2340 = BKR_TRUE;
                    } else {
                        vec_push(_v2343, _v345);
                        if (_v2315(_v2343)) {
                            _v2340 = BKR_TRUE;
                        }
                    }
                }
            }
            if ((_v2339 && _v2340)) {
                _v2331 = BKR_TRUE;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_bool _v2344(_v436 _v621) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        if ((_v597(_v925(_v621, _v1172)) == _v289)) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2345(_v436 _v621) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        _v433 _v473 = _v925(_v621, _v1172);
        if ((_v597(_v473) == _v289)) {
            return _v598(_v473);
        }
        _v1172 = (_v1172 + 1);
    }
    return (-1);
}

_v428 _v2346(_v341 _v1546, bkr_i64 _v2347) {
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v259)) {
            if ((_v1168(_v563) == _v2347)) {
                return _v563;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v564();
}

bkr_bool _v2348(_v435 _v977, _v436 _v621, bkr_i64 _v2347, bkr_i64 _v1403) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        if (((_v1172 < _v916(_v977)) && (_v918(_v977, _v1172) != 0))) {
            _v1172 = (_v1172 + 1);
            continue;
        }
        _v433 _v473 = _v925(_v621, _v1172);
        if (_v2296(_v473)) {
            return BKR_TRUE;
        }
        if ((_v597(_v473) == _v289)) {
            if ((_v598(_v473) == _v2347)) {
                if ((_v599(_v473) == _v1403)) {
                    return BKR_TRUE;
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2349(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v426 _v542, _v436 _v621, bkr_str _v2015) {
    if ((!_v2344(_v621))) {
        return _v1254;
    }
    bkr_i64 _v2347 = _v2345(_v621);
    if ((_v2347 < 0)) {
        return _v1254;
    }
    _v428 _v2350 = _v2346(_v1546, _v2347);
    if (_v566(_v2350)) {
        return _v1254;
    }
    _v435 _v1166 = _v1169(_v2350);
    if ((_v916(_v1166) <= 0)) {
        return _v1254;
    }
    _v435 _v977 = _v751(_v542);
    bkr_str _v2329 = "";
    bkr_i64 _v1645 = 0;
    while ((_v1645 < _v916(_v1166))) {
        bkr_i64 _v1403 = _v918(_v1166, _v1645);
        if ((!_v2348(_v977, _v621, _v2347, _v1403))) {
            bkr_str _v2351 = bkr_str_concat(bkr_str_concat(_v1959(_v425, _v2347), "."), _v1959(_v425, _v1403));
            if ((bkr_len((bkr_str)(intptr_t)(_v2329)) > 0)) {
                _v2329 = bkr_str_concat(bkr_str_concat(_v2329, ", "), _v2351);
            } else {
                _v2329 = _v2351;
            }
        }
        _v1645 = (_v1645 + 1);
    }
    if ((bkr_len((bkr_str)(intptr_t)(_v2329)) <= 0)) {
        return _v1254;
    }
    return _v1964(_v1254, _v2214("non_exhaustive_match", "BKR_SELF_EXHAUSTIVENESS", "match", _v2015, _v547(_v542), "patterns covering every declared enum variant", bkr_str_concat("missing ", _v2329), "Add the missing enum pattern arm or a catch-all pattern."));
}

bkr_i64 _v2352(bkr_i64 _v1254, _v426 _v542, _v436 _v621, bkr_i64 _v1731, bkr_str _v2015) {
    if (((_v2344(_v621) || _v2314(_v621)) || _v2336(_v621))) {
        return _v1254;
    }
    if (((!_v2187(_v1731)) && (_v1731 != _v306))) {
        return _v1254;
    }
    _v435 _v977 = _v751(_v542);
    bkr_i64 _v1172 = 0;
    bkr_bool _v2353 = BKR_FALSE;
    while ((_v1172 < _v920(_v621))) {
        if (((_v1172 < _v916(_v977)) && (_v918(_v977, _v1172) != 0))) {
            _v1172 = (_v1172 + 1);
            continue;
        }
        _v433 _v473 = _v925(_v621, _v1172);
        if (_v2296(_v473)) {
            _v2353 = BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    if (_v2353) {
        return _v1254;
    }
    return _v1964(_v1254, _v2214("non_exhaustive_match", "BKR_SELF_EXHAUSTIVENESS", "match", _v2015, _v547(_v542), "patterns covering all values or a catch-all pattern", "missing catch-all pattern", "Add a wildcard '_' arm or identifier pattern to cover all remaining values."));
}

bkr_i64 _v2354(bkr_i64 _v1254, _v341 _v1546, _v435 _v977, _v436 _v621, bkr_str _v2015) {
    if ((!_v2344(_v621))) {
        return _v1254;
    }
    bkr_i64 _v2347 = _v2345(_v621);
    if ((_v2347 < 0)) {
        return _v1254;
    }
    _v428 _v2350 = _v2346(_v1546, _v2347);
    if (_v566(_v2350)) {
        return _v1254;
    }
    _v435 _v1166 = _v1169(_v2350);
    bkr_i64 _v2355 = _v916(_v1166);
    if ((_v2355 <= 0)) {
        return _v1254;
    }
    bkr_i64 _v2356 = 0;
    bkr_bool _v2331 = BKR_FALSE;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        bkr_bool _v2309 = ((_v1172 < _v916(_v977)) && (_v918(_v977, _v1172) != 0));
        _v433 _v473 = _v925(_v621, _v1172);
        if (_v2331) {
            _v1254 = _v2306(_v1254, "unreachable_match_pattern", bkr_str_concat("match pattern ", int_to_string((_v1172 + 1))), _v2015, _v473, "reachable match pattern", "previous enum patterns already cover every declared variant", "Remove this arm or move it before the exhaustive enum patterns.");
        }
        if ((!_v2309)) {
            if ((_v597(_v473) == _v289)) {
                bkr_i64 _v1403 = _v599(_v473);
                if ((_v598(_v473) == _v2347)) {
                    if (_v2357(_v1166, _v1403)) {
                        if ((!_v2358(_v621, _v2347, _v1403, _v1172))) {
                            _v2356 = (_v2356 + 1);
                        }
                    }
                }
            }
            if ((_v2356 >= _v2355)) {
                _v2331 = BKR_TRUE;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_bool _v2357(_v435 _v1166, bkr_i64 _v1403) {
    bkr_i64 _v1645 = 0;
    while ((_v1645 < _v916(_v1166))) {
        if ((_v918(_v1166, _v1645) == _v1403)) {
            return BKR_TRUE;
        }
        _v1645 = (_v1645 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2358(_v436 _v621, bkr_i64 _v2347, bkr_i64 _v1403, bkr_i64 _v2359) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v2359)) {
        _v433 _v473 = _v925(_v621, _v1172);
        if ((_v597(_v473) == _v289)) {
            if ((_v598(_v473) == _v2347)) {
                if ((_v599(_v473) == _v1403)) {
                    return BKR_TRUE;
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2360(bkr_i64 _v1254, _v1547 _v2202, _v434 _v995, bkr_str _v2015) {
    bkr_i64 _v2190 = _v316;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v995))) {
        _v341 _v2030 = _v913(_v995, _v1172);
        _v426 _v2361 = _v540(_v2030);
        bkr_i64 _v2362 = _v2203(_v2202, _v2361);
        _v1254 = _v2239(_v1254, _v2202, _v2361, bkr_str_concat("array element ", int_to_string((_v1172 + 1))), _v2015);
        if ((_v2190 == _v316)) {
            if ((_v2362 != _v316)) {
                _v2190 = _v2362;
            }
        } else {
            _v1254 = _v2257(_v1254, "array_element_type_mismatch", bkr_str_concat("array element ", int_to_string((_v1172 + 1))), _v2015, _v2030, _v2190, _v2362, "Make every array literal element produce the same type.");
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2363(bkr_i64 _v1254, bkr_i64 _v1671, bkr_str _v2015, bkr_i64 _v2364) {
    if (_v524(_v1671)) {
        return _v1254;
    }
    return _v2365(_v1254, _v538(_v1671), _v2015, _v2364);
}

bkr_i64 _v2365(bkr_i64 _v1254, _v426 _v542, bkr_str _v2015, bkr_i64 _v2364) {
    bkr_i64 _v319 = _v545(_v542);
    if ((_v319 == _v261)) {
        _v1254 = _v2365(_v1254, _v695(_v542), _v2015, _v2364);
        _v434 _v1016 = _v699(_v542);
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v907(_v1016))) {
            _v1254 = _v2365(_v1254, _v540(_v913(_v1016, _v1172)), _v2015, _v2364);
            _v1172 = (_v1172 + 1);
        }
    } else {
        if ((_v319 == _v244)) {
            _v434 _v1016 = _v692(_v542);
            bkr_i64 _v1172 = 0;
            while ((_v1172 < _v907(_v1016))) {
                _v1254 = _v2365(_v1254, _v540(_v913(_v1016, _v1172)), _v2015, _v2364);
                _v1172 = (_v1172 + 1);
            }
        } else {
            if ((_v319 == _v257)) {
                _v434 _v1009 = _v731(_v542);
                bkr_i64 _v1172 = 0;
                while ((_v1172 < _v907(_v1009))) {
                    _v1254 = _v2365(_v1254, _v540(_v913(_v1009, _v1172)), _v2015, _v2364);
                    _v1172 = (_v1172 + 1);
                }
                bkr_i64 _v403 = _v1006(_v542);
                if ((_v403 != 0)) {
                    _v1254 = _v2363(_v1254, _v403, _v2015, _v2364);
                }
            } else {
                if ((_v319 == _v256)) {
                    _v1254 = _v2363(_v1254, _v720(_v542), _v2015, _v2364);
                } else {
                    if ((_v319 == _v242)) {
                        _v1254 = _v2363(_v1254, _v675(_v542), _v2015, _v2364);
                        _v1254 = _v2363(_v1254, _v678(_v542), _v2015, _v2364);
                    } else {
                        if ((_v319 == _v240)) {
                            _v1254 = _v2363(_v1254, _v778(_v542), _v2015, _v2364);
                        } else {
                            if ((_v319 == _v241)) {
                                _v1254 = _v2363(_v1254, _v782(_v542), _v2015, _v2364);
                            } else {
                                if ((_v319 == _v243)) {
                                    _v1254 = _v2363(_v1254, _v685(_v542), _v2015, _v2364);
                                } else {
                                    if ((_v319 == _v250)) {
                                        _v1254 = _v2363(_v1254, _v734(_v542), _v2015, _v2364);
                                        _v1254 = _v2363(_v1254, _v737(_v542), _v2015, _v2364);
                                        _v1254 = _v2363(_v1254, _v740(_v542), _v2015, _v2364);
                                    } else {
                                        if ((_v319 == _v239)) {
                                            _v1254 = _v2365(_v1254, _v705(_v542), _v2015, _v2364);
                                        } else {
                                            if ((_v319 == _v252)) {
                                                _v434 _v995 = _v702(_v542);
                                                bkr_i64 _v1172 = 0;
                                                while ((_v1172 < _v907(_v995))) {
                                                    _v1254 = _v2365(_v1254, _v540(_v913(_v995, _v1172)), _v2015, _v2364);
                                                    _v1172 = (_v1172 + 1);
                                                }
                                            } else {
                                                if ((_v319 == _v253)) {
                                                    _v1254 = _v2363(_v1254, _v712(_v542), _v2015, _v2364);
                                                    _v1254 = _v2363(_v1254, _v715(_v542), _v2015, _v2364);
                                                } else {
                                                    if ((_v319 == _v227)) {
                                                        _v1254 = _v2366(_v1254, _v581(_v547(_v542)), _v2015, _v2364);
                                                    } else {
                                                        if ((_v319 == _v258)) {
                                                            _v1254 = _v2363(_v1254, _v743(_v542), _v2015, _v2364);
                                                            _v434 _v976 = _v749(_v542);
                                                            bkr_i64 _v1172 = 0;
                                                            while ((_v1172 < _v907(_v976))) {
                                                                _v341 _v1127 = _v913(_v976, _v1172);
                                                                if ((_v510(_v1127) == _v227)) {
                                                                    _v1254 = _v2366(_v1254, _v581(_v1127), _v2015, _v2364);
                                                                } else {
                                                                    _v1254 = _v2365(_v1254, _v540(_v1127), _v2015, _v2364);
                                                                }
                                                                _v1172 = (_v1172 + 1);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1254;
}

bkr_i64 _v2367(bkr_i64 _v1254, _v427 _v554, bkr_str _v2015, bkr_i64 _v2364) {
    bkr_i64 _v319 = _v556(_v554);
    if (((_v319 == _v234) || (_v319 == _v235))) {
        if ((_v2364 <= 0)) {
            _v1254 = _v2225(_v1254, _v2015, _v554);
        }
    } else {
        if ((_v319 == _v228)) {
            _v1254 = _v2363(_v1254, _v764(_v554), _v2015, _v2364);
        } else {
            if ((_v319 == _v229)) {
                _v1254 = _v2363(_v1254, _v769(_v554), _v2015, _v2364);
            } else {
                if ((_v319 == _v230)) {
                    _v1254 = _v2363(_v1254, _v828(_v554), _v2015, _v2364);
                    _v1254 = _v2366(_v1254, _v830(_v554), _v2015, _v2364);
                    bkr_i64 _v377 = _v833(_v554);
                    if (_v526(_v377)) {
                        _v1254 = _v2366(_v1254, _v579(_v377), _v2015, _v2364);
                    }
                } else {
                    if ((_v319 == _v231)) {
                        _v1254 = _v2363(_v1254, _v850(_v554), _v2015, _v2364);
                        _v1254 = _v2366(_v1254, _v852(_v554), _v2015, (_v2364 + 1));
                    } else {
                        if ((_v319 == _v236)) {
                            _v1254 = _v2363(_v1254, _v838(_v554), _v2015, _v2364);
                            _v1254 = _v2363(_v1254, _v841(_v554), _v2015, _v2364);
                            _v1254 = _v2366(_v1254, _v845(_v554), _v2015, (_v2364 + 1));
                        } else {
                            if ((_v319 == _v237)) {
                                _v1254 = _v2366(_v1254, _v847(_v554), _v2015, (_v2364 + 1));
                            } else {
                                if ((_v319 == _v233)) {
                                    _v1254 = _v2363(_v1254, _v855(_v554), _v2015, _v2364);
                                    _v1254 = _v2363(_v1254, _v858(_v554), _v2015, _v2364);
                                } else {
                                    if ((_v319 == _v238)) {
                                        _v1254 = _v2367(_v1254, _v550(_v773(_v554)), _v2015, _v2364);
                                    } else {
                                        if ((_v319 == _v232)) {
                                            _v1254 = _v2363(_v1254, _v861(_v554), _v2015, _v2364);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1254;
}

bkr_i64 _v2366(bkr_i64 _v1254, _v429 _v583, bkr_str _v2015, bkr_i64 _v2364) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        _v1254 = _v2367(_v1254, _v1111(_v583, _v1172), _v2015, _v2364);
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_bool _v2368(_v427 _v554) {
    bkr_i64 _v319 = _v556(_v554);
    if ((_v319 == _v229)) {
        return BKR_TRUE;
    }
    if ((_v319 == _v230)) {
        bkr_i64 _v377 = _v833(_v554);
        if (_v524(_v377)) {
            return BKR_FALSE;
        }
        return (_v2369(_v830(_v554)) && _v2369(_v579(_v377)));
    }
    return BKR_FALSE;
}

bkr_bool _v2369(_v429 _v583) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        if (_v2368(_v1111(_v583, _v1172))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2370(_v427 _v554) {
    bkr_i64 _v319 = _v556(_v554);
    if ((((_v319 == _v229) || (_v319 == _v234)) || (_v319 == _v235))) {
        return BKR_TRUE;
    }
    if ((_v319 == _v230)) {
        bkr_i64 _v377 = _v833(_v554);
        if (_v524(_v377)) {
            return BKR_FALSE;
        }
        return (_v2371(_v830(_v554)) && _v2371(_v579(_v377)));
    }
    return BKR_FALSE;
}

bkr_bool _v2371(_v429 _v583) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        if (_v2370(_v1111(_v583, _v1172))) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_i64 _v2372(bkr_i64 _v1254, _v427 _v554, bkr_str _v2015) {
    bkr_i64 _v319 = _v556(_v554);
    if ((_v319 == _v230)) {
        _v1254 = _v2373(_v1254, _v830(_v554), _v2015);
        bkr_i64 _v377 = _v833(_v554);
        if (_v526(_v377)) {
            _v1254 = _v2373(_v1254, _v579(_v377), _v2015);
        }
    } else {
        if ((_v319 == _v231)) {
            _v1254 = _v2373(_v1254, _v852(_v554), _v2015);
        } else {
            if ((_v319 == _v236)) {
                _v1254 = _v2373(_v1254, _v845(_v554), _v2015);
            } else {
                if ((_v319 == _v237)) {
                    _v1254 = _v2373(_v1254, _v847(_v554), _v2015);
                }
            }
        }
    }
    return _v1254;
}

bkr_i64 _v2373(bkr_i64 _v1254, _v429 _v583, bkr_str _v2015) {
    bkr_bool _v2374 = BKR_FALSE;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        _v427 _v554 = _v1111(_v583, _v1172);
        if (_v2374) {
            _v1254 = _v2240(_v1254, _v2015, _v554);
        } else {
            _v1254 = _v2372(_v1254, _v554, _v2015);
            if (_v2370(_v554)) {
                _v2374 = BKR_TRUE;
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2375(bkr_i64 _v1254, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v1671, bkr_str _v2015, bkr_str _v2376, bkr_str _v1363, bkr_i64 _v2190, bkr_str _v2117) {
    if (_v524(_v1671)) {
        if (((_v2190 != _v307) && (_v2190 != _v316))) {
            bkr_i64 _v2377 = _v475(_v229);
            _v1254 = _v2219(_v1254, _v2376, _v1363, _v2015, _v2377, _v2190, _v307, _v2117);
        }
        return _v1254;
    }
    return _v2378(_v1254, _v425, _v2202, _v538(_v1671), _v2015, _v2376, _v1363, _v2190, _v2117);
}

bkr_i64 _v2378(bkr_i64 _v1254, bkr_i64 _v425, _v1547 _v2202, _v426 _v542, bkr_str _v2015, bkr_str _v2376, bkr_str _v1363, bkr_i64 _v2190, bkr_str _v2117) {
    bkr_i64 _v2191 = _v2203(_v2202, _v542);
    return _v2257(_v1254, _v2376, _v1363, _v2015, _v547(_v542), _v2190, _v2191, _v2117);
}

bkr_i64 _v2379(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v368, bkr_str _v2015) {
    return _v2380(_v1254, _v477(_v0), _v425, _v2202, _v539(_v368), _v2015);
}

bkr_i64 _v2380(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, _v426 _v542, bkr_str _v2015) {
    bkr_i64 _v355 = _v689(_v542);
    _v428 _v1530 = _v2265(_v1546, _v355);
    if (_v566(_v1530)) {
        _v428 _v1539 = _v2271(_v1546, _v355);
        if (_v567(_v1539)) {
            bkr_str _v2381 = _v1959(_v425, _v355);
            _v434 _v1016 = _v692(_v542);
            _v434 _v1162 = _v890(_v1539);
            bkr_i64 _v1806 = _v907(_v1016);
            bkr_i64 _v2382 = _v907(_v1162);
            if ((_v1806 != _v2382)) {
                bkr_str _v2254 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Call struct constructor ", _v2381), " with exactly "), int_to_string(_v2382)), " argument(s), or update the struct definition.");
                _v1254 = _v2221(_v1254, "call_argument_count_mismatch", _v2381, _v2015, _v547(_v542), _v2382, _v1806, _v2254);
            }
            bkr_i64 _v1172 = 0;
            while (((_v1172 < _v1806) && (_v1172 < _v2382))) {
                _v341 _v1447 = _v913(_v1162, _v1172);
                bkr_i64 _v1158 = _v895(_v1447);
                _v341 _v2256 = _v913(_v1016, _v1172);
                _v426 _v1440 = _v540(_v2256);
                bkr_i64 _v2190 = _v2064(_v1546, _v517(_v1158));
                bkr_i64 _v2191 = _v2203(_v2202, _v1440);
                bkr_str _v2128 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Change argument ", int_to_string((_v1172 + 1))), " for "), _v2381), " to match field "), _v1959(_v425, _v892(_v1447))), " or update the struct definition.");
                _v1254 = _v2257(_v1254, "call_argument_type_mismatch", _v2381, _v2015, _v2256, _v2190, _v2191, _v2128);
                _v1172 = (_v1172 + 1);
            }
            return _v1254;
        }
        if ((_v2251(_v1959(_v425, _v355)) < 0)) {
            _v1254 = _v2269(_v1254, _v1546, _v425, _v542, _v2015);
        }
        return _v2258(_v1254, _v425, _v2202, _v542, _v2015);
    }
    bkr_str _v2037 = _v1959(_v425, _v355);
    _v434 _v1016 = _v692(_v542);
    _v434 _v1145 = _v872(_v1530);
    bkr_i64 _v1806 = _v907(_v1016);
    bkr_i64 _v2267 = _v907(_v1145);
    if ((_v1806 != _v2267)) {
        bkr_str _v2254 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Call ", _v2037), " with exactly "), int_to_string(_v2267)), " argument(s), or update the function signature.");
        _v1254 = _v2221(_v1254, "call_argument_count_mismatch", _v2037, _v2015, _v547(_v542), _v2267, _v1806, _v2254);
    }
    bkr_i64 _v1172 = 0;
    while (((_v1172 < _v1806) && (_v1172 < _v2267))) {
        _v341 _v1523 = _v913(_v1145, _v1172);
        bkr_i64 _v2102 = _v866(_v1523);
        _v341 _v2256 = _v913(_v1016, _v1172);
        _v426 _v1440 = _v540(_v2256);
        bkr_i64 _v2190 = _v2064(_v1546, _v517(_v2102));
        bkr_i64 _v2191 = _v2203(_v2202, _v1440);
        bkr_str _v2128 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Change argument ", int_to_string((_v1172 + 1))), " for "), _v2037), " to match parameter "), _v1959(_v425, _v863(_v1523))), " or update the function signature.");
        _v1254 = _v2257(_v1254, "call_argument_type_mismatch", _v2037, _v2015, _v2256, _v2190, _v2191, _v2128);
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2383(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v1671, bkr_str _v2015, bkr_i64 _v2384) {
    return _v2385(_v1254, _v477(_v0), _v425, _v2202, _v1671, _v2015, _v2384);
}

bkr_i64 _v2385(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v1671, bkr_str _v2015, bkr_i64 _v2384) {
    if (_v524(_v1671)) {
        return _v1254;
    }
    return _v2386(_v1254, _v1546, _v425, _v2202, _v538(_v1671), _v2015, _v2384);
}

bkr_i64 _v2386(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, _v426 _v542, bkr_str _v2015, bkr_i64 _v2384) {
    bkr_i64 _v319 = _v545(_v542);
    if ((_v319 == _v261)) {
        _v426 _v1022 = _v695(_v542);
        bkr_i64 _v2387 = _v2203(_v2202, _v1022);
        if ((_v2387 != _v309)) {
            bkr_str _v2128 = "Methods can only be invoked on struct instances.";
            _v1254 = _v2264(_v1254, "invalid_method_call_target", "receiver", _v2015, _v547(_v1022), _v309, _v2387, _v2128);
        }
        _v1254 = _v2386(_v1254, _v1546, _v425, _v2202, _v1022, _v2015, _v2384);
        _v434 _v1016 = _v699(_v542);
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v907(_v1016))) {
            _v341 _v2256 = _v913(_v1016, _v1172);
            _v426 _v2388 = _v540(_v2256);
            _v1254 = _v2239(_v1254, _v2202, _v2388, bkr_str_concat("method argument ", int_to_string((_v1172 + 1))), _v2015);
            _v1254 = _v2386(_v1254, _v1546, _v425, _v2202, _v2388, _v2015, _v2384);
            _v1172 = (_v1172 + 1);
        }
    } else {
        if ((_v319 == _v244)) {
            _v1254 = _v2380(_v1254, _v1546, _v425, _v2202, _v542, _v2015);
            _v434 _v1016 = _v692(_v542);
            bkr_i64 _v1172 = 0;
            while ((_v1172 < _v907(_v1016))) {
                _v341 _v2256 = _v913(_v1016, _v1172);
                _v426 _v2388 = _v540(_v2256);
                _v1254 = _v2239(_v1254, _v2202, _v2388, bkr_str_concat("call argument ", int_to_string((_v1172 + 1))), _v2015);
                _v1254 = _v2386(_v1254, _v1546, _v425, _v2202, _v2388, _v2015, _v2384);
                _v1172 = (_v1172 + 1);
            }
        } else {
            if ((_v319 == _v257)) {
                bkr_i64 _v1519 = _v725(_v542);
                bkr_str _v1697 = _v1959(_v425, _v1519);
                _v435 _v1008 = _v728(_v542);
                _v434 _v1009 = _v731(_v542);
                _v1254 = _v2274(_v1254, _v425, _v542, _v2015);
                _v1254 = _v2276(_v1254, _v1546, _v425, _v542, _v2015);
                bkr_i64 _v1172 = 0;
                while ((_v1172 < _v907(_v1009))) {
                    bkr_i64 _v1674 = _v918(_v1008, _v1172);
                    bkr_str _v1045 = _v1959(_v425, _v1674);
                    _v341 _v1437 = _v913(_v1009, _v1172);
                    _v426 _v2389 = _v540(_v1437);
                    _v1254 = _v2386(_v1254, _v1546, _v425, _v2202, _v2389, _v2015, _v2384);
                    _v1254 = _v2239(_v1254, _v2202, _v2389, bkr_str_concat(bkr_str_concat(_v1697, "."), _v1045), _v2015);
                    bkr_i64 _v2190 = _v2273(_v1546, _v1519, _v1674);
                    bkr_i64 _v2191 = _v2203(_v2202, _v2389);
                    bkr_str _v2128 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Change field ", _v1045), " for struct "), _v1697), " to match the declared field type.");
                    _v1254 = _v2264(_v1254, "struct_field_type_mismatch", bkr_str_concat(bkr_str_concat(_v1697, "."), _v1045), _v2015, _v1437, _v2190, _v2191, _v2128);
                    _v1172 = (_v1172 + 1);
                }
                bkr_i64 _v403 = _v1006(_v542);
                if ((_v403 != 0)) {
                    _v1254 = _v2386(_v1254, _v1546, _v425, _v2202, _v538(_v403), _v2015, _v2384);
                }
            } else {
                if ((_v319 == _v256)) {
                    _v1254 = _v2285(_v1254, _v2202, _v542, _v2015);
                    _v1254 = _v2239(_v1254, _v2202, _v538(_v720(_v542)), "field access base", _v2015);
                    _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v720(_v542), _v2015, _v2384);
                } else {
                    if ((_v319 == _v242)) {
                        if (_v2282(_v2202, _v542)) {
                            _v426 _v1051 = _v538(_v675(_v542));
                            if ((_v545(_v1051) == _v242)) {
                                bkr_i64 _v1785 = _v672(_v1051);
                                if ((_v1785 == _v178)) {
                                    bkr_i64 _v2390 = _v675(_v1051);
                                    return _v2385(_v1254, _v1546, _v425, _v2202, _v2390, _v2015, _v2384);
                                }
                                if ((_v1785 == _v176)) {
                                    _v426 _v1788 = _v538(_v675(_v1051));
                                    _v426 _v1789 = _v538(_v678(_v1051));
                                    if (((_v545(_v1788) == _v242) && (_v545(_v1789) == _v242))) {
                                        _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v675(_v1788), _v2015, _v2384);
                                        return _v2385(_v1254, _v1546, _v425, _v2202, _v675(_v1789), _v2015, _v2384);
                                    }
                                }
                            }
                            return _v1254;
                        }
                        _v1254 = _v2280(_v1254, _v2202, _v542, _v2015);
                        _v1254 = _v2239(_v1254, _v2202, _v538(_v675(_v542)), "binary left operand", _v2015);
                        _v1254 = _v2239(_v1254, _v2202, _v538(_v678(_v542)), "binary right operand", _v2015);
                        _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v675(_v542), _v2015, _v2384);
                        _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v678(_v542), _v2015, _v2384);
                    } else {
                        if ((_v319 == _v240)) {
                            _v1254 = _v2239(_v1254, _v2202, _v538(_v778(_v542)), "try operand", _v2015);
                            _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v778(_v542), _v2015, _v2384);
                        } else {
                            if ((_v319 == _v241)) {
                                _v426 _v1694 = _v784(_v542);
                                _v346 _v1450 = _v785(_v542);
                                _v1254 = _v2239(_v1254, _v2202, _v1694, "cast operand", _v2015);
                                _v1254 = _v2386(_v1254, _v1546, _v425, _v2202, _v1694, _v2015, _v2384);
                                bkr_i64 _v2195 = _v2203(_v2202, _v1694);
                                bkr_i64 _v1803 = _v2064(_v1546, _v1450);
                                if ((!_v2194(_v2195, _v1803))) {
                                    bkr_str _v2128 = "Cast between compatible numeric types, bool, or between i64 and handle types.";
                                    _v1254 = _v2220(_v1254, "cast_type_mismatch", "cast expression", _v2015, _v547(_v542), _v1803, _v2195, _v2128);
                                }
                            } else {
                                if ((_v319 == _v243)) {
                                    _v1254 = _v2283(_v1254, _v2202, _v542, _v2015);
                                    _v1254 = _v2239(_v1254, _v2202, _v538(_v685(_v542)), "unary operand", _v2015);
                                    _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v685(_v542), _v2015, _v2384);
                                } else {
                                    if ((_v319 == _v250)) {
                                        _v426 _v1418 = _v538(_v737(_v542));
                                        _v426 _v1419 = _v538(_v740(_v542));
                                        bkr_i64 _v1693 = _v2203(_v2202, _v1418);
                                        bkr_i64 _v2391 = _v2203(_v2202, _v1419);
                                        _v1254 = _v2264(_v1254, "ternary_branch_type_mismatch", "ternary else branch", _v2015, _v547(_v1419), _v1693, _v2391, "Make both ternary branches produce compatible value types.");
                                        _v1254 = _v2378(_v1254, _v425, _v2202, _v538(_v734(_v542)), _v2015, "condition_type_mismatch", "ternary condition", _v305, "Make this ternary condition produce bool.");
                                        _v1254 = _v2239(_v1254, _v2202, _v538(_v734(_v542)), "ternary condition", _v2015);
                                        _v1254 = _v2239(_v1254, _v2202, _v1418, "ternary then branch", _v2015);
                                        _v1254 = _v2239(_v1254, _v2202, _v1419, "ternary else branch", _v2015);
                                        _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v734(_v542), _v2015, _v2384);
                                        _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v737(_v542), _v2015, _v2384);
                                        _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v740(_v542), _v2015, _v2384);
                                    } else {
                                        if ((_v319 == _v239)) {
                                            _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v704(_v542), _v2015, _v2384);
                                        } else {
                                            if ((_v319 == _v252)) {
                                                _v434 _v995 = _v702(_v542);
                                                _v1254 = _v2360(_v1254, _v2202, _v995, _v2015);
                                                bkr_i64 _v1172 = 0;
                                                while ((_v1172 < _v907(_v995))) {
                                                    _v341 _v2030 = _v913(_v995, _v1172);
                                                    _v1254 = _v2386(_v1254, _v1546, _v425, _v2202, _v540(_v2030), _v2015, _v2384);
                                                    _v1172 = (_v1172 + 1);
                                                }
                                            } else {
                                                if ((_v319 == _v253)) {
                                                    _v1254 = _v2287(_v1254, _v2202, _v542, _v2015);
                                                    _v1254 = _v2239(_v1254, _v2202, _v538(_v712(_v542)), "index base", _v2015);
                                                    _v426 _v2392 = _v538(_v715(_v542));
                                                    bkr_i64 _v2393 = _v2203(_v2202, _v2392);
                                                    _v1254 = _v2257(_v1254, "index_type_mismatch", "index expression", _v2015, _v547(_v2392), _v303, _v2393, "Use an integer-compatible index expression.");
                                                    _v1254 = _v2239(_v1254, _v2202, _v2392, "index expression", _v2015);
                                                    _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v712(_v542), _v2015, _v2384);
                                                    _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v715(_v542), _v2015, _v2384);
                                                } else {
                                                    if ((_v319 == _v227)) {
                                                        _v1254 = _v2394(_v1254, _v1546, _v425, _v2202, _v581(_v547(_v542)), _v2015, _v2384);
                                                    } else {
                                                        if ((_v319 == _v258)) {
                                                            _v426 _v975 = _v538(_v743(_v542));
                                                            bkr_i64 _v1731 = _v2203(_v2202, _v975);
                                                            _v1254 = _v2386(_v1254, _v1546, _v425, _v2202, _v975, _v2015, _v2384);
                                                            _v435 _v977 = _v751(_v542);
                                                            _v1254 = _v2307(_v1254, _v977, _v746(_v542), _v2015);
                                                            _v1254 = _v2294(_v1254, _v746(_v542), _v1731, _v2015);
                                                            _v1254 = _v2326(_v1254, _v542, _v746(_v542), _v1731, _v2015);
                                                            _v1254 = _v2332(_v1254, _v542, _v746(_v542), _v2015);
                                                            _v1254 = _v2338(_v1254, _v542, _v746(_v542), _v2015);
                                                            _v1254 = _v2349(_v1254, _v1546, _v425, _v542, _v746(_v542), _v2015);
                                                            _v1254 = _v2352(_v1254, _v542, _v746(_v542), _v1731, _v2015);
                                                            _v1254 = _v2330(_v1254, _v977, _v746(_v542), _v1731, _v2015);
                                                            _v1254 = _v2335(_v1254, _v977, _v746(_v542), _v2015);
                                                            _v1254 = _v2341(_v1254, _v977, _v746(_v542), _v2015);
                                                            _v1254 = _v2354(_v1254, _v1546, _v977, _v746(_v542), _v2015);
                                                            bkr_i64 _v574 = 0;
                                                            while ((_v574 < _v916(_v977))) {
                                                                bkr_i64 _v2167 = _v918(_v977, _v574);
                                                                if ((_v2167 != 0)) {
                                                                    _v1254 = _v2386(_v1254, _v1546, _v425, _v2202, _v538(_v2167), _v2015, _v2384);
                                                                }
                                                                _v574 = (_v574 + 1);
                                                            }
                                                            _v434 _v976 = _v749(_v542);
                                                            _v1254 = _v2289(_v1254, _v2202, _v976, _v2015);
                                                            bkr_i64 _v1172 = 0;
                                                            while ((_v1172 < _v907(_v976))) {
                                                                _v341 _v1127 = _v913(_v976, _v1172);
                                                                if ((_v510(_v1127) == _v227)) {
                                                                    _v1254 = _v2394(_v1254, _v1546, _v425, _v2202, _v581(_v1127), _v2015, _v2384);
                                                                } else {
                                                                    _v426 _v2395 = _v540(_v1127);
                                                                    _v1254 = _v2239(_v1254, _v2202, _v2395, "match arm value", _v2015);
                                                                    _v1254 = _v2386(_v1254, _v1546, _v425, _v2202, _v2395, _v2015, _v2384);
                                                                }
                                                                _v1172 = (_v1172 + 1);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1254;
}

bkr_i64 _v2396(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v370, bkr_str _v2015, bkr_i64 _v2384) {
    return _v2397(_v1254, _v477(_v0), _v425, _v2202, _v551(_v370), _v2015, _v2384);
}

bkr_i64 _v2397(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, _v427 _v554, bkr_str _v2015, bkr_i64 _v2384) {
    _v341 _v2090 = _v587(_v554);
    bkr_i64 _v319 = _v556(_v554);
    if ((_v319 == _v228)) {
        bkr_i64 _v366 = _v764(_v554);
        bkr_str _v1363 = _v1959(_v425, _v758(_v554));
        _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v366, _v2015, _v2384);
        bkr_i64 _v516 = _v761(_v554);
        if ((_v526(_v516) && _v526(_v366))) {
            bkr_i64 _v2190 = _v2064(_v1546, _v517(_v516));
            bkr_i64 _v2191 = _v2203(_v2202, _v538(_v366));
            bkr_str _v2128 = bkr_str_concat(bkr_str_concat("Change the initializer for ", _v1363), " or update the declared local type.");
            _v1254 = _v2264(_v1254, "annotation_type_mismatch", _v1363, _v2015, _v2090, _v2190, _v2191, _v2128);
        } else {
            if ((_v524(_v516) && _v2243(_v366))) {
                _v1254 = _v2229(_v1254, _v1363, _v2015, _v538(_v366));
            } else {
                if ((_v524(_v516) && _v2245(_v425, _v366))) {
                    _v1254 = _v2230(_v1254, _v1363, _v2015, _v538(_v366));
                } else {
                    if ((_v524(_v516) && _v2247(_v425, _v366))) {
                        _v1254 = _v2231(_v1254, _v1363, _v2015, _v538(_v366));
                    } else {
                        if ((_v524(_v516) && _v2249(_v425, _v366))) {
                            _v1254 = _v2232(_v1254, _v1363, _v2015, _v538(_v366));
                        } else {
                            if ((_v524(_v516) && _v2250(_v2202, _v366))) {
                                _v1254 = _v2233(_v1254, _v1363, _v2015, _v538(_v366));
                            }
                        }
                    }
                }
            }
        }
        _v2093(_v2202, _v554);
    } else {
        if ((_v319 == _v229)) {
            bkr_i64 _v2398 = _v769(_v554);
            _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v2398, _v2015, _v2384);
            if (_v524(_v2398)) {
                if (((_v2384 != _v307) && (_v2384 != _v316))) {
                    _v1254 = _v2220(_v1254, "return_type_mismatch", "return", _v2015, _v2090, _v2384, _v307, "Return a value matching the function return type or change the function signature.");
                }
            } else {
                _v1254 = _v2239(_v1254, _v2202, _v538(_v2398), "return value", _v2015);
                bkr_i64 _v2191 = _v2203(_v2202, _v538(_v2398));
                _v1254 = _v2264(_v1254, "return_type_mismatch", "return", _v2015, _v2090, _v2384, _v2191, "Return a value matching the function return type or change the function signature.");
            }
        } else {
            if ((_v319 == _v230)) {
                bkr_i64 _v375 = _v828(_v554);
                _v1254 = _v2378(_v1254, _v425, _v2202, _v538(_v375), _v2015, "condition_type_mismatch", "if condition", _v305, "Make this if condition produce bool.");
                _v1254 = _v2239(_v1254, _v2202, _v538(_v375), "if condition", _v2015);
                _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v375, _v2015, _v2384);
                _v1254 = _v2394(_v1254, _v1546, _v425, _v2202, _v830(_v554), _v2015, _v2384);
                bkr_i64 _v377 = _v833(_v554);
                if (_v526(_v377)) {
                    _v1254 = _v2394(_v1254, _v1546, _v425, _v2202, _v579(_v377), _v2015, _v2384);
                }
            } else {
                if ((_v319 == _v231)) {
                    bkr_i64 _v375 = _v850(_v554);
                    _v1254 = _v2378(_v1254, _v425, _v2202, _v538(_v375), _v2015, "condition_type_mismatch", "while condition", _v305, "Make this while condition produce bool.");
                    _v1254 = _v2239(_v1254, _v2202, _v538(_v375), "while condition", _v2015);
                    _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v375, _v2015, _v2384);
                    _v1254 = _v2394(_v1254, _v1546, _v425, _v2202, _v852(_v554), _v2015, _v2384);
                } else {
                    if ((_v319 == _v236)) {
                        bkr_i64 _v339 = _v838(_v554);
                        bkr_i64 _v382 = _v841(_v554);
                        _v1254 = _v2378(_v1254, _v425, _v2202, _v538(_v339), _v2015, "for_range_type_mismatch", "for range start", _v303, "Make the for range start numeric.");
                        _v1254 = _v2378(_v1254, _v425, _v2202, _v538(_v382), _v2015, "for_range_type_mismatch", "for range end", _v303, "Make the for range end numeric.");
                        _v1254 = _v2239(_v1254, _v2202, _v538(_v339), "for range start", _v2015);
                        _v1254 = _v2239(_v1254, _v2202, _v538(_v382), "for range end", _v2015);
                        _v1608(_v2202, _v835(_v554), _v303);
                        _v1254 = _v2394(_v1254, _v1546, _v425, _v2202, _v845(_v554), _v2015, _v2384);
                    } else {
                        if ((_v319 == _v237)) {
                            _v1254 = _v2394(_v1254, _v1546, _v425, _v2202, _v847(_v554), _v2015, _v2384);
                        } else {
                            if ((_v319 == _v233)) {
                                bkr_i64 _v386 = _v855(_v554);
                                bkr_i64 _v387 = _v858(_v554);
                                _v426 _v1098 = _v538(_v386);
                                if ((!_v2241(_v1098))) {
                                    _v1254 = _v2224(_v1254, _v2015, _v1098);
                                }
                                if (((_v545(_v1098) == _v245) && _v567(_v2270(_v1546, _v663(_v1098))))) {
                                    _v1254 = _v2227(_v1254, _v425, _v2015, _v1098);
                                }
                                _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v386, _v2015, _v2384);
                                _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v387, _v2015, _v2384);
                                _v1254 = _v2239(_v1254, _v2202, _v538(_v387), "assignment value", _v2015);
                                bkr_i64 _v2190 = _v2203(_v2202, _v1098);
                                bkr_i64 _v2191 = _v2203(_v2202, _v538(_v387));
                                _v1254 = _v2264(_v1254, "assignment_type_mismatch", "assignment", _v2015, _v2090, _v2190, _v2191, "Assign a value that matches the target type.");
                            } else {
                                if ((_v319 == _v238)) {
                                    _v1254 = _v2397(_v1254, _v1546, _v425, _v2202, _v550(_v773(_v554)), _v2015, _v2384);
                                } else {
                                    if ((_v319 == _v232)) {
                                        _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v861(_v554), _v2015, _v2384);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return _v1254;
}

bkr_i64 _v2399(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v578, bkr_str _v2015, bkr_i64 _v2384) {
    return _v2394(_v1254, _v477(_v0), _v425, _v2202, _v580(_v578), _v2015, _v2384);
}

bkr_i64 _v2394(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, _v429 _v583, bkr_str _v2015, bkr_i64 _v2384) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        _v1254 = _v2397(_v1254, _v1546, _v425, _v2202, _v1111(_v583, _v1172), _v2015, _v2384);
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_i64 _v2400(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, _v1547 _v2202, bkr_i64 _v558, bkr_str _v2035) {
    return _v2401(_v1254, _v477(_v0), _v425, _v2202, _v560(_v558), _v2035);
}

bkr_i64 _v2401(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v1547 _v2202, _v428 _v563, bkr_str _v2035) {
    _v341 _v1981 = _v588(_v563);
    bkr_str _v2228 = _v1959(_v425, _v879(_v563));
    bkr_i64 _v387 = _v885(_v563);
    _v1254 = _v2385(_v1254, _v1546, _v425, _v2202, _v387, _v2035, _v316);
    bkr_i64 _v516 = _v882(_v563);
    if ((_v526(_v516) && _v526(_v387))) {
        bkr_i64 _v2190 = _v2064(_v1546, _v517(_v516));
        bkr_i64 _v2191 = _v2203(_v2202, _v538(_v387));
        bkr_str _v2128 = bkr_str_concat(bkr_str_concat("Change the initializer for ", _v2228), " or update the declared constant type.");
        _v1254 = _v2264(_v1254, "annotation_type_mismatch", _v2228, _v2035, _v1981, _v2190, _v2191, _v2128);
    } else {
        if ((_v524(_v516) && _v2243(_v387))) {
            _v1254 = _v2229(_v1254, _v2228, _v2035, _v538(_v387));
        } else {
            if ((_v524(_v516) && _v2245(_v425, _v387))) {
                _v1254 = _v2230(_v1254, _v2228, _v2035, _v538(_v387));
            } else {
                if ((_v524(_v516) && _v2247(_v425, _v387))) {
                    _v1254 = _v2231(_v1254, _v2228, _v2035, _v538(_v387));
                } else {
                    if ((_v524(_v516) && _v2249(_v425, _v387))) {
                        _v1254 = _v2232(_v1254, _v2228, _v2035, _v538(_v387));
                    } else {
                        if ((_v524(_v516) && _v2250(_v2202, _v387))) {
                            _v1254 = _v2233(_v1254, _v2228, _v2035, _v538(_v387));
                        }
                    }
                }
            }
        }
    }
    return _v1254;
}

bkr_i64 _v2402(bkr_i64 _v1254, bkr_i64 _v0, bkr_i64 _v425, bkr_i64 _v558) {
    return _v2403(_v1254, _v477(_v0), _v425, _v560(_v558));
}

bkr_i64 _v2403(bkr_i64 _v1254, _v341 _v1546, bkr_i64 _v425, _v428 _v563) {
    bkr_str _v2037 = _v1959(_v425, _v869(_v563));
    bkr_str _v2015 = bkr_str_concat("function:", _v2037);
    _v1547 _v2202 = _v2101(_v1546, _v563);
    bkr_i64 _v2384 = _v2209(_v1546, _v563);
    _v1254 = _v2366(_v1254, _v877(_v563), _v2015, 0);
    _v1254 = _v2373(_v1254, _v877(_v563), _v2015);
    if (((((_v2384 != _v307) && (_v2384 != _v314)) && (_v2384 != _v316)) && (!_v2369(_v877(_v563))))) {
        _v1254 = _v2238(_v1254, _v425, _v2015, _v563);
    }
    return _v2394(_v1254, _v1546, _v425, _v2202, _v877(_v563), _v2015, _v2384);
}

bkr_i64 _v2404(bkr_i64 _v1254, bkr_i64 _v0) {
    return _v2405(_v1254, _v477(_v0));
}

bkr_i64 _v2405(bkr_i64 _v1254, _v341 _v1546) {
    bkr_i64 _v425 = _v904(_v1546);
    bkr_str _v2035 = bkr_str_concat("kernel:", _v1959(_v425, _v664(_v1546)));
    _v1547 _v2202 = _v2068(_v1546);
    _v434 _v1186 = _v899(_v1546);
    _v1254 = _v2266(_v1254, _v1546, _v425, _v2035);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        bkr_i64 _v319 = _v569(_v563);
        if ((_v319 == _v249)) {
            _v1254 = _v2401(_v1254, _v1546, _v425, _v2202, _v563, _v2035);
        } else {
            if ((_v319 == _v224)) {
                _v1254 = _v2403(_v1254, _v1546, _v425, _v563);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_str _v2406(bkr_i64 _v0) {
    bkr_str _v1955 = ",";
    bkr_i64 _v1254 = _v1960();
    _v341 _v1546 = _v477(_v0);
    bkr_bool _v2007 = _v1947(_v1546);
    if (_v2007) {
        _v2405(_v1254, _v1546);
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.self_host.typecheck.v1")), _v1955), _v1907("representation", "typecheck_pass")), _v1955), _v1909("complete", BKR_TRUE)), _v1955), _v1909("truncated", (!_v2007))), _v1955), _v1909("annotation_checks", BKR_TRUE)), _v1955), _v1909("return_checks", BKR_TRUE)), _v1955), _v1909("condition_checks", BKR_TRUE)), _v1955), _v1909("call_argument_checks", BKR_TRUE)), _v1955), _v1909("call_arity_checks", BKR_TRUE)), _v1955), _v1909("call_target_checks", BKR_TRUE)), _v1955), _v1909("builtin_arity_checks", BKR_TRUE)), _v1955), _v1909("builtin_argument_type_checks", BKR_TRUE)), _v1955), _v1909("entry_point_checks", BKR_TRUE)), _v1955), _v1909("entry_signature_checks", BKR_TRUE)), _v1955), _v1909("assignment_target_checks", BKR_TRUE)), _v1955), _v1909("const_assignment_checks", BKR_TRUE)), _v1955), _v1909("struct_field_value_checks", BKR_TRUE)), _v1955), _v1909("struct_field_shape_checks", BKR_TRUE)), _v1955), _v1909("ambiguous_empty_array_checks", BKR_TRUE)), _v1955), _v1909("ambiguous_none_checks", BKR_TRUE)), _v1955), _v1909("ambiguous_result_constructor_checks", BKR_TRUE)), _v1955), _v1909("ambiguous_collection_constructor_checks", BKR_TRUE)), _v1955), _v1909("index_base_type_checks", BKR_TRUE)), _v1955), _v1909("index_type_checks", BKR_TRUE)), _v1955), _v1909("binary_operand_checks", BKR_TRUE)), _v1955), _v1909("unary_operand_checks", BKR_TRUE)), _v1955), _v1909("field_access_base_checks", BKR_TRUE)), _v1955), _v1909("ternary_branch_checks", BKR_TRUE)), _v1955), _v1909("match_arm_type_checks", BKR_TRUE)), _v1955), _v1909("match_pattern_type_checks", BKR_TRUE)), _v1955), _v1909("match_pattern_semantic_checks", BKR_TRUE)), _v1955), _v1909("bool_match_exhaustiveness_checks", BKR_TRUE)), _v1955), _v1909("option_match_exhaustiveness_checks", BKR_TRUE)), _v1955), _v1909("result_match_exhaustiveness_checks", BKR_TRUE)), _v1955), _v1909("enum_match_exhaustiveness_checks", BKR_TRUE)), _v1955), _v1909("scalar_match_exhaustiveness_checks", BKR_TRUE)), _v1955), _v1909("finite_match_redundancy_checks", BKR_TRUE)), _v1955), _v1909("array_element_type_checks", BKR_TRUE)), _v1955), _v1909("loop_control_checks", BKR_TRUE)), _v1955), _v1909("return_path_checks", BKR_TRUE)), _v1955), _v1909("unreachable_code_checks", BKR_TRUE)), _v1955), _v1909("semantic_validation_passes", BKR_TRUE)), _v1955), _v1909("void_value_checks", BKR_TRUE)), _v1955), _v1909("compound_void_value_checks", BKR_TRUE)), _v1955), _v1909("full_value_context_void_checks", BKR_TRUE)), _v1955), _v1909("typed_diagnostic_context", BKR_TRUE)), _v1955), _v1909("structured_repair_metadata", BKR_TRUE)), _v1955), _v1909("diagnostic_phase_field", BKR_TRUE)), _v1955), _v1909("diagnostic_rule_ids", BKR_TRUE)), _v1955), _v1909("diagnostic_severity", BKR_TRUE)), _v1955), _v1909("diagnostic_severity_counts", BKR_TRUE)), _v1955), _v1909("suggested_edit_envelope", BKR_TRUE)), _v1955), _v1909("has_diagnostics", (_v1963(_v1254) > 0))), _v1955), _v1908("diagnostic_count", _v1963(_v1254))), _v1955), _v1908("error_count", _v1963(_v1254))), _v1955), _v1908("warning_count", 0)), _v1955), _v1907("known_limits", "Typecheck pass enforces declared annotations, return values and return paths, void value use, conditions, ternary branches, match patterns and arm values, array elements, loop-control context, unreachable statements, assignments, index bases, field-access bases, operands, calls, and struct literal shapes; full language subset semantic checking active.")), _v1955), _v1910("diagnostics", _v1961(_v1254))), "}");
}

bkr_str _v2407(bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_TYPECHECK_JSON: ", _v2406(_v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_i64 _v2408(bkr_i64 _v1254, _v341 _v1546) {
    bkr_i64 _v425 = _v904(_v1546);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v1186))) {
        _v428 _v563 = _v914(_v1186, _v1172);
        bkr_i64 _v319 = _v569(_v563);
        if ((_v319 == _v224)) {
            bkr_str _v2037 = _v1959(_v425, _v869(_v563));
            bkr_str _v2015 = bkr_str_concat("function:", _v2037);
            bkr_i64 _v2384 = _v2209(_v1546, _v563);
            _v1254 = _v2366(_v1254, _v877(_v563), _v2015, 0);
            _v1254 = _v2373(_v1254, _v877(_v563), _v2015);
            if (((((_v2384 != _v307) && (_v2384 != _v314)) && (_v2384 != _v316)) && (!_v2369(_v877(_v563))))) {
                _v1254 = _v2238(_v1254, _v425, _v2015, _v563);
            }
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1254;
}

bkr_str _v2409(bkr_i64 _v0) {
    bkr_str _v1955 = ",";
    bkr_i64 _v1254 = _v1960();
    _v341 _v1546 = _v477(_v0);
    _v1254 = _v2408(_v1254, _v1546);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.self_host.semantic.v1")), _v1955), _v1907("representation", "semantic_validation_pass")), _v1955), _v1909("complete", BKR_TRUE)), _v1955), _v1909("loop_control_validation", BKR_TRUE)), _v1955), _v1909("unreachable_code_detection", BKR_TRUE)), _v1955), _v1909("return_path_validation", BKR_TRUE)), _v1955), _v1909("assignment_target_validation", BKR_TRUE)), _v1955), _v1909("const_assignment_validation", BKR_TRUE)), _v1955), _v1909("has_diagnostics", (_v1963(_v1254) > 0))), _v1955), _v1908("diagnostic_count", _v1963(_v1254))), _v1955), _v1908("error_count", _v1963(_v1254))), _v1955), _v1908("warning_count", 0)), _v1955), _v1910("diagnostics", _v1961(_v1254))), "}");
}

bkr_str _v2410(bkr_i64 _v0) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_SEMANTIC_JSON: ", _v2409(_v0)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v2423(_v2411 _v2424, bkr_i64 _v1036) {
    if (((_v1036 >= 0) && (_v1036 < vec_len(_v2424._v425)))) {
        return vec_get(_v2424._v425, _v1036);
    }
    return "";
}

bkr_bool _v2425(_v2411 _v2424, bkr_str _v2426, bkr_str _v1363, _v341 _v452, bkr_str _v1279, bkr_str _v2213, bkr_str _v2128) {
    _v1964(_v2424._v2412, _v2214(_v2426, "BKR_SELF_SEMANTIC", _v1363, vec_get(_v2424._v2015, 0), _v452, _v1279, _v2213, _v2128));
    return BKR_FALSE;
}

bkr_str _v2427(bkr_i64 _v319) {
    if (((_v319 == _v302) || (_v319 == _v303))) {
        return "i";
    }
    if ((_v319 == _v305)) {
        return "b";
    }
    if ((_v319 == _v306)) {
        return "s";
    }
    if ((_v319 == _v304)) {
        return "f";
    }
    return "?";
}

bkr_str _v2428(_v2411 _v2424, _v346 _v521) {
    if (_v523(_v521)) {
        return "";
    }
    bkr_i64 _v319 = _v530(_v521);
    if ((_v319 == _v309)) {
        bkr_str _v1363 = _v2423(_v2424, _v532(_v521));
        if (hashmap_contains(_v2424._v2416, ((bkr_i64)(intptr_t)_v1363))) {
            return bkr_str_concat("S:", _v1363);
        }
        if (hashmap_contains(_v2424._v2413, ((bkr_i64)(intptr_t)_v1363))) {
            return "e";
        }
        return "";
    }
    if ((_v319 == _v308)) {
        return "A";
    }
    if ((_v319 == _v310)) {
        return bkr_str_concat("V:", _v2427(_v535(_v521)));
    }
    if ((_v319 == _v311)) {
        return bkr_str_concat(bkr_str_concat("M:", _v2427(_v535(_v521))), _v2427(_v536(_v521)));
    }
    if ((_v319 == _v313)) {
        return bkr_str_concat(bkr_str_concat("R:", _v2427(_v535(_v521))), _v2427(_v536(_v521)));
    }
    if ((_v319 == _v312)) {
        return bkr_str_concat("O:", _v2427(_v535(_v521)));
    }
    bkr_str _v1244 = _v2427(_v319);
    if (bkr_str_eq(_v1244, "?")) {
        return "";
    }
    return _v1244;
}

bkr_str _v2430(_v2411 _v2424, bkr_i64 _v342) {
    if ((!_v526(_v342))) {
        return "";
    }
    return _v2428(_v2424, _v517(_v342));
}

bkr_bool _v2431(bkr_str _v2432) {
    return (starts_with(_v2432, "S:") || bkr_str_eq(_v2432, "A"));
}

bkr_bool _v2433(bkr_str _v2432) {
    return (((bkr_str_eq(_v2432, "i") || bkr_str_eq(_v2432, "b")) || bkr_str_eq(_v2432, "s")) || bkr_str_eq(_v2432, "f"));
}

bkr_str _v2434(bkr_str _v2432, bkr_i64 _v362) {
    if ((_v362 < bkr_len((bkr_str)(intptr_t)(_v2432)))) {
        return char_at(_v2432, _v362);
    }
    return "?";
}

bkr_str _v2435(bkr_str _v1363) {
    if ((((((((((((((((bkr_str_eq(_v1363, "char_at") || bkr_str_eq(_v1363, "substring")) || bkr_str_eq(_v1363, "trim")) || bkr_str_eq(_v1363, "int_to_string")) || bkr_str_eq(_v1363, "from_char_code")) || bkr_str_eq(_v1363, "join_lines")) || bkr_str_eq(_v1363, "read_file")) || bkr_str_eq(_v1363, "arg_at")) || bkr_str_eq(_v1363, "str_replace")) || bkr_str_eq(_v1363, "str_to_upper")) || bkr_str_eq(_v1363, "str_to_lower")) || bkr_str_eq(_v1363, "str_repeat")) || bkr_str_eq(_v1363, "path_join")) || bkr_str_eq(_v1363, "path_dir")) || bkr_str_eq(_v1363, "path_base")) || bkr_str_eq(_v1363, "path_ext"))) {
        return "s";
    }
    if (((((((((bkr_str_eq(_v1363, "len") || bkr_str_eq(_v1363, "strlen")) || bkr_str_eq(_v1363, "vec_len")) || bkr_str_eq(_v1363, "hashmap_len")) || bkr_str_eq(_v1363, "char_code")) || bkr_str_eq(_v1363, "char_code_at")) || bkr_str_eq(_v1363, "parse_int")) || bkr_str_eq(_v1363, "str_index_of")) || bkr_str_eq(_v1363, "args_count"))) {
        return "i";
    }
    if ((((((((bkr_str_eq(_v1363, "contains") || bkr_str_eq(_v1363, "starts_with")) || bkr_str_eq(_v1363, "ends_with")) || bkr_str_eq(_v1363, "file_exists")) || bkr_str_eq(_v1363, "hashmap_contains")) || bkr_str_eq(_v1363, "vec_is_empty")) || bkr_str_eq(_v1363, "result_is_ok")) || bkr_str_eq(_v1363, "result_is_err"))) {
        return "b";
    }
    return "";
}

bkr_i64 _v2436(_v2411 _v2424, bkr_str _v1363) {
    bkr_i64 _v1172 = (vec_len(_v2424._v2419) - 1);
    while ((_v1172 >= 0)) {
        if (bkr_str_eq(vec_get(_v2424._v2419, _v1172), _v1363)) {
            return _v1172;
        }
        _v1172 = (_v1172 - 1);
    }
    return (-1);
}

bkr_bool _v2437(_v2411 _v2424, bkr_str _v1363, bkr_str _v2432, bkr_bool _v2438) {
    vec_push(_v2424._v2419, ((bkr_i64)(intptr_t)_v1363));
    vec_push(_v2424._v2420, ((bkr_i64)(intptr_t)_v2432));
    if (_v2438) {
        vec_push(_v2424._v2421, 1);
    } else {
        vec_push(_v2424._v2421, 0);
    }
    vec_push(_v2424._v2422, 0);
    return BKR_TRUE;
}

bkr_i64 _v2439(_v2411 _v2424) {
    return vec_len(_v2424._v2419);
}

bkr_bool _v2440(_v2411 _v2424, bkr_i64 _v2441) {
    while ((vec_len(_v2424._v2419) > _v2441)) {
        vec_pop(_v2424._v2419);
        vec_pop(_v2424._v2420);
        vec_pop(_v2424._v2421);
        vec_pop(_v2424._v2422);
    }
    return BKR_TRUE;
}

bkr_i64 _v2443(_v2411 _v2424) {
    bkr_i64 _v2444 = vec_new();
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v2424._v2422))) {
        vec_push(_v2444, vec_get(_v2424._v2422, _v1172));
        _v1172 = (_v1172 + 1);
    }
    return _v2444;
}

bkr_bool _v2445(_v2411 _v2424, bkr_i64 _v2444) {
    bkr_i64 _v1172 = 0;
    while (((_v1172 < vec_len(_v2444)) && (_v1172 < vec_len(_v2424._v2422)))) {
        vec_set(_v2424._v2422, _v1172, vec_get(_v2444, _v1172));
        _v1172 = (_v1172 + 1);
    }
    return BKR_TRUE;
}

bkr_bool _v2446(_v2411 _v2424, bkr_i64 _v2447) {
    bkr_i64 _v1172 = 0;
    while (((_v1172 < vec_len(_v2447)) && (_v1172 < vec_len(_v2424._v2422)))) {
        if ((vec_get(_v2424._v2422, _v1172) == 1)) {
            vec_set(_v2447, _v1172, 1);
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_TRUE;
}

bkr_str _v2448(_v2411 _v2424, _v426 _v542) {
    bkr_i64 _v319 = _v545(_v542);
    if ((_v319 == _v246)) {
        return "i";
    }
    if ((_v319 == _v247)) {
        return "b";
    }
    if ((_v319 == _v248)) {
        return "s";
    }
    if ((_v319 == _v251)) {
        return "f";
    }
    if (((_v319 == _v252) || (_v319 == _v239))) {
        return "A";
    }
    if ((_v319 == _v257)) {
        return bkr_str_concat("S:", _v2423(_v2424, _v725(_v542)));
    }
    if ((_v319 == _v245)) {
        bkr_i64 _v1172 = _v2436(_v2424, _v2423(_v2424, _v663(_v542)));
        if ((_v1172 >= 0)) {
            return vec_get(_v2424._v2420, _v1172);
        }
        return "";
    }
    if ((_v319 == _v241)) {
        return _v2430(_v2424, _v783(_v542));
    }
    if ((_v319 == _v244)) {
        bkr_str _v1363 = _v2423(_v2424, _v689(_v542));
        if (hashmap_contains(_v2424._v2416, ((bkr_i64)(intptr_t)_v1363))) {
            return bkr_str_concat("S:", _v1363);
        }
        if (hashmap_contains(_v2424._v2418, ((bkr_i64)(intptr_t)_v1363))) {
            bkr_str _v2449 = (bkr_str)(intptr_t)(hashmap_get(_v2424._v2418, ((bkr_i64)(intptr_t)_v1363)));
            return _v2449;
        }
        return _v2435(_v1363);
    }
    if ((_v319 == _v261)) {
        bkr_str _v2451 = _v2452(_v2424, _v542);
        if (hashmap_contains(_v2424._v2418, ((bkr_i64)(intptr_t)_v2451))) {
            bkr_str _v2449 = (bkr_str)(intptr_t)(hashmap_get(_v2424._v2418, ((bkr_i64)(intptr_t)_v2451)));
            return _v2449;
        }
        return "";
    }
    if ((_v319 == _v256)) {
        bkr_str _v2453 = _v2448(_v2424, _v721(_v542));
        if (starts_with(_v2453, "S:")) {
            bkr_str _v1841 = bkr_str_concat(bkr_str_concat(substring(_v2453, 2, bkr_len((bkr_str)(intptr_t)(_v2453))), "."), _v2423(_v2424, _v723(_v542)));
            if (hashmap_contains(_v2424._v2417, ((bkr_i64)(intptr_t)_v1841))) {
                bkr_str _v1154 = (bkr_str)(intptr_t)(hashmap_get(_v2424._v2417, ((bkr_i64)(intptr_t)_v1841)));
                return _v1154;
            }
        }
        return "";
    }
    if ((_v319 == _v242)) {
        bkr_i64 _v349 = _v672(_v542);
        if (((((((((_v349 == _v166) || (_v349 == _v167)) || (_v349 == _v168)) || (_v349 == _v169)) || (_v349 == _v170)) || (_v349 == _v171)) || (_v349 == _v172)) || (_v349 == _v173))) {
            return "b";
        }
        bkr_str _v350 = _v2448(_v2424, _v538(_v675(_v542)));
        if (((_v349 == _v161) && bkr_str_eq(_v350, "s"))) {
            return "s";
        }
        if (bkr_str_eq(_v350, "i")) {
            return "i";
        }
        return "";
    }
    return "";
}

bkr_str _v2452(_v2411 _v2424, _v426 _v542) {
    bkr_str _v2454 = _v2448(_v2424, _v695(_v542));
    if ((!starts_with(_v2454, "S:"))) {
        return "";
    }
    return bkr_str_concat(bkr_str_concat(substring(_v2454, 2, bkr_len((bkr_str)(intptr_t)(_v2454))), "::"), _v2423(_v2424, _v697(_v542)));
}

bkr_bool _v2455(_v2411 _v2424, _v426 _v542, bkr_str _v1363) {
    bkr_i64 _v339 = _v546(_v542);
    if (((_v339 < 0) || ((_v339 + bkr_len((bkr_str)(intptr_t)(_v1363))) > bkr_len((bkr_str)(intptr_t)(_v2424._v1212))))) {
        return BKR_TRUE;
    }
    return (!bkr_str_eq(substring(_v2424._v1212, _v339, (_v339 + bkr_len((bkr_str)(intptr_t)(_v1363)))), _v1363));
}

bkr_bool _v2456(_v2411 _v2424, bkr_i64 _v342) {
    _v426 _v542 = _v538(_v342);
    if ((_v545(_v542) != _v245)) {
        return BKR_TRUE;
    }
    bkr_str _v1363 = _v2423(_v2424, _v663(_v542));
    bkr_i64 _v1172 = _v2436(_v2424, _v1363);
    if ((((_v1172 < 0) || (!_v2431(vec_get(_v2424._v2420, _v1172)))) || _v2455(_v2424, _v542, _v1363))) {
        return BKR_TRUE;
    }
    vec_set(_v2424._v2422, _v1172, 1);
    return BKR_TRUE;
}

bkr_bool _v2457(_v2411 _v2424, bkr_str _v2458, bkr_i64 _v2459, bkr_str _v2460, bkr_str _v2461) {
    _v426 _v1099 = _v538(_v2459);
    bkr_str _v2213 = _v2448(_v2424, _v1099);
    if ((((!_v2433(_v2458)) || (!_v2433(_v2213))) || bkr_str_eq(_v2458, _v2213))) {
        return BKR_TRUE;
    }
    return _v2425(_v2424, "collection_value_mismatch", _v2461, _v547(_v1099), _v2462(_v2458), _v2462(_v2213), bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Pass a ", _v2462(_v2458)), " "), _v2460), " to match the declared type."));
}

bkr_bool _v2463(bkr_str _v1363) {
    if (((((bkr_str_eq(_v1363, "vec_new") || bkr_str_eq(_v1363, "hashmap_new")) || bkr_str_eq(_v1363, "hashmap_new_str")) || bkr_str_eq(_v1363, "result_ok")) || bkr_str_eq(_v1363, "result_err"))) {
        return BKR_FALSE;
    }
    return ((starts_with(_v1363, "vec_") || starts_with(_v1363, "hashmap_")) || starts_with(_v1363, "result_"));
}

bkr_str _v2462(bkr_str _v1244) {
    if (bkr_str_eq(_v1244, "i")) {
        return "integer";
    }
    if (bkr_str_eq(_v1244, "b")) {
        return "bool";
    }
    if (bkr_str_eq(_v1244, "s")) {
        return "str";
    }
    if (bkr_str_eq(_v1244, "f")) {
        return "float";
    }
    return "unknown";
}

bkr_bool _v2464(_v2411 _v2424, _v426 _v542) {
    bkr_str _v1363 = _v2423(_v2424, _v689(_v542));
    if (hashmap_contains(_v2424._v2418, ((bkr_i64)(intptr_t)_v1363))) {
        return BKR_TRUE;
    }
    _v434 _v1016 = _v692(_v542);
    bkr_i64 _v2465 = _v907(_v1016);
    if ((_v2465 == 0)) {
        return BKR_TRUE;
    }
    _v426 _v1456 = _v538(_v910(_v1016, 0));
    bkr_str _v2466 = _v2448(_v2424, _v1456);
    if (((bkr_str_eq(_v2466, "i") && (_v545(_v1456) == _v245)) && _v2463(_v1363))) {
        return _v2425(_v2424, "raw_handle_use", _v2423(_v2424, _v663(_v1456)), _v547(_v1456), "a typed Vec, HashMap or Result value", "integer", "Pass the typed collection itself; an integer is not a Vec, HashMap or Result handle.");
    }
    if (((bkr_str_eq(_v1363, "vec_push") && (_v2465 == 2)) && starts_with(_v2466, "V:"))) {
        return _v2457(_v2424, _v2434(_v2466, 2), _v910(_v1016, 1), "element", _v1363);
    }
    if (((bkr_str_eq(_v1363, "hashmap_insert") && (_v2465 == 3)) && starts_with(_v2466, "M:"))) {
        _v2457(_v2424, _v2434(_v2466, 2), _v910(_v1016, 1), "key", _v1363);
        return _v2457(_v2424, _v2434(_v2466, 3), _v910(_v1016, 2), "value", _v1363);
    }
    if ((bkr_str_eq(_v1363, "result_value") && starts_with(_v2466, "R:"))) {
        bkr_str _v2467 = _v2434(_v2466, 2);
        bkr_str _v2468 = _v2434(_v2466, 3);
        if (((_v2433(_v2467) && _v2433(_v2468)) && (!bkr_str_eq(_v2467, _v2468)))) {
            return _v2425(_v2424, "ambiguous_result_value", _v1363, _v547(_v542), "Result with matching Ok and Err types", bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Result<", _v2462(_v2467)), ", "), _v2462(_v2468)), ">"), "Use result_unwrap or result_unwrap_err, or match on Ok/Err, so the value has one type.");
        }
    }
    return BKR_TRUE;
}

bkr_bool _v2469(_v2411 _v2424, bkr_str _v2169, bkr_i64 _v2470) {
    _v426 _v1709 = _v538(_v2470);
    if (((!starts_with(_v2169, "R:")) || (_v545(_v1709) != _v244))) {
        return BKR_TRUE;
    }
    bkr_str _v1363 = _v2423(_v2424, _v689(_v1709));
    _v434 _v1016 = _v692(_v1709);
    if ((hashmap_contains(_v2424._v2418, ((bkr_i64)(intptr_t)_v1363)) || (_v907(_v1016) != 1))) {
        return BKR_TRUE;
    }
    bkr_i64 _v1817 = _v910(_v1016, 0);
    if ((bkr_str_eq(_v1363, "result_ok") || bkr_str_eq(_v1363, "Ok"))) {
        return _v2457(_v2424, _v2434(_v2169, 2), _v1817, "Ok value", _v1363);
    }
    if ((bkr_str_eq(_v1363, "result_err") || bkr_str_eq(_v1363, "Err"))) {
        return _v2457(_v2424, _v2434(_v2169, 3), _v1817, "Err value", _v1363);
    }
    return BKR_TRUE;
}

bkr_bool _v2471(_v2411 _v2424, bkr_i64 _v342, bkr_bool _v2472) {
    if ((!_v526(_v342))) {
        return BKR_TRUE;
    }
    return _v2473(_v2424, _v538(_v342), _v2472);
}

bkr_bool _v2474(_v2411 _v2424, _v434 _v2475) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v907(_v2475))) {
        _v2471(_v2424, _v910(_v2475, _v1172), BKR_TRUE);
        _v1172 = (_v1172 + 1);
    }
    return BKR_TRUE;
}

bkr_bool _v2473(_v2411 _v2424, _v426 _v542, bkr_bool _v2472) {
    bkr_i64 _v319 = _v545(_v542);
    if ((_v319 == _v245)) {
        bkr_str _v1363 = _v2423(_v2424, _v663(_v542));
        bkr_i64 _v1172 = _v2436(_v2424, _v1363);
        if (((_v1172 >= 0) && (vec_get(_v2424._v2422, _v1172) == 1))) {
            vec_set(_v2424._v2422, _v1172, 0);
            return _v2425(_v2424, "use_after_move", _v1363, _v547(_v542), "a value that has not been moved", "moved value", bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Use `copy ", _v1363), "` where it was moved, or stop using "), _v1363), " after the move."));
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v256)) {
        _v426 _v1038 = _v721(_v542);
        if ((_v545(_v1038) == _v245)) {
            bkr_str _v2476 = _v2423(_v2424, _v663(_v1038));
            if (((_v2436(_v2424, _v2476) < 0) && hashmap_contains(_v2424._v2413, ((bkr_i64)(intptr_t)_v2476)))) {
                bkr_str _v2477 = _v2423(_v2424, _v723(_v542));
                if ((!hashmap_contains(_v2424._v2415, ((bkr_i64)(intptr_t)bkr_str_concat(bkr_str_concat(_v2476, "."), _v2477))))) {
                    return _v2425(_v2424, "unknown_enum_variant", bkr_str_concat(bkr_str_concat(_v2476, "."), _v2477), _v547(_v542), bkr_str_concat("a variant of enum ", _v2476), _v2477, bkr_str_concat(bkr_str_concat("Use one of the variants declared in enum ", _v2476), "."));
                }
                return BKR_TRUE;
            }
        }
        return _v2473(_v2424, _v1038, BKR_TRUE);
    }
    if ((_v319 == _v244)) {
        _v2474(_v2424, _v692(_v542));
        return _v2464(_v2424, _v542);
    }
    if ((_v319 == _v261)) {
        _v426 _v1022 = _v695(_v542);
        _v2473(_v2424, _v1022, BKR_TRUE);
        _v2474(_v2424, _v699(_v542));
        bkr_str _v2454 = _v2448(_v2424, _v1022);
        bkr_str _v2451 = _v2452(_v2424, _v542);
        if ((starts_with(_v2454, "S:") && (!hashmap_contains(_v2424._v2418, ((bkr_i64)(intptr_t)_v2451))))) {
            return _v2425(_v2424, "method_not_found", _v2451, _v547(_v542), bkr_str_concat("a method declared as fn ", _v2451), "no such method", bkr_str_concat(bkr_str_concat("Declare fn ", _v2451), " or call an existing method."));
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v257)) {
        bkr_str _v1363 = _v2423(_v2424, _v725(_v542));
        _v434 _v615 = _v731(_v542);
        _v2474(_v2424, _v615);
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v907(_v615))) {
            _v2456(_v2424, _v910(_v615, _v1172));
            _v1172 = (_v1172 + 1);
        }
        bkr_i64 _v403 = _v1006(_v542);
        if ((_v403 != 0)) {
            _v2471(_v2424, _v403, BKR_TRUE);
            bkr_str _v2453 = _v2448(_v2424, _v538(_v403));
            if ((starts_with(_v2453, "S:") && (!bkr_str_eq(_v2453, bkr_str_concat("S:", _v1363))))) {
                return _v2425(_v2424, "struct_update_base_mismatch", _v1363, _v547(_v538(_v403)), _v1363, substring(_v2453, 2, bkr_len((bkr_str)(intptr_t)(_v2453))), bkr_str_concat(bkr_str_concat("The ..base value must be a ", _v1363), "."));
            }
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v252)) {
        _v434 _v2478 = _v702(_v542);
        _v2474(_v2424, _v2478);
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v907(_v2478))) {
            _v2456(_v2424, _v910(_v2478, _v1172));
            _v1172 = (_v1172 + 1);
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v239)) {
        return _v2473(_v2424, _v705(_v542), BKR_TRUE);
    }
    if ((_v319 == _v241)) {
        _v426 _v1381 = _v538(_v782(_v542));
        _v2473(_v2424, _v1381, BKR_TRUE);
        return BKR_TRUE;
    }
    if ((_v319 == _v242)) {
        _v2471(_v2424, _v675(_v542), BKR_TRUE);
        return _v2471(_v2424, _v678(_v542), BKR_TRUE);
    }
    if ((_v319 == _v243)) {
        return _v2471(_v2424, _v685(_v542), BKR_TRUE);
    }
    if ((_v319 == _v240)) {
        return _v2471(_v2424, _v778(_v542), BKR_TRUE);
    }
    if ((_v319 == _v253)) {
        _v2471(_v2424, _v712(_v542), BKR_TRUE);
        return _v2471(_v2424, _v715(_v542), BKR_TRUE);
    }
    if ((_v319 == _v250)) {
        _v2471(_v2424, _v734(_v542), BKR_TRUE);
        _v2471(_v2424, _v737(_v542), _v2472);
        return _v2471(_v2424, _v740(_v542), _v2472);
    }
    if ((_v319 == _v227)) {
        return _v2479(_v2424, _v579(_v541(_v542)));
    }
    if ((_v319 == _v258)) {
        return _v2480(_v2424, _v542, _v2472);
    }
    return BKR_TRUE;
}

bkr_bool _v2481(_v2411 _v2424, _v433 _v473, _v341 _v452) {
    bkr_i64 _v319 = _v597(_v473);
    if ((((_v319 == _v287) || (_v319 == _v290)) || (_v319 == _v291))) {
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            return _v2481(_v2424, _v592(_v345), _v452);
        }
        return BKR_TRUE;
    }
    if ((_v319 != _v289)) {
        return BKR_TRUE;
    }
    bkr_str _v1642 = _v2423(_v2424, _v598(_v473));
    bkr_str _v2477 = _v2423(_v2424, _v599(_v473));
    bkr_str _v1841 = bkr_str_concat(bkr_str_concat(_v1642, "."), _v2477);
    if ((!hashmap_contains(_v2424._v2413, ((bkr_i64)(intptr_t)_v1642)))) {
        return BKR_TRUE;
    }
    if ((!hashmap_contains(_v2424._v2415, ((bkr_i64)(intptr_t)_v1841)))) {
        return _v2425(_v2424, "unknown_enum_variant", _v1841, _v452, bkr_str_concat("a variant of enum ", _v1642), _v2477, bkr_str_concat(bkr_str_concat("Use one of the variants declared in enum ", _v1642), "."));
    }
    bkr_i64 _v2482 = hashmap_get(_v2424._v2415, ((bkr_i64)(intptr_t)_v1841));
    bkr_i64 _v2483 = 0;
    if ((_v600(_v473) >= 0)) {
        _v2483 = (_v2483 + 1);
    }
    if ((_v601(_v473) >= 0)) {
        _v2483 = (_v2483 + 1);
    }
    if (((_v2483 > 0) && (_v2483 != _v2482))) {
        return _v2425(_v2424, "enum_pattern_arity", _v1841, _v452, bkr_str_concat(int_to_string(_v2482), " binding(s)"), bkr_str_concat(int_to_string(_v2483), " binding(s)"), bkr_str_concat(bkr_str_concat("Bind exactly the payload values declared for ", _v1841), "."));
    }
    return BKR_TRUE;
}

bkr_bool _v2484(_v429 _v583) {
    bkr_i64 _v399 = _v590(_v583);
    if ((_v399 == 0)) {
        return BKR_FALSE;
    }
    bkr_i64 _v2485 = _v556(_v1111(_v583, (_v399 - 1)));
    return (!((((((_v2485 == _v228) || (_v2485 == _v233)) || (_v2485 == _v231)) || (_v2485 == _v236)) || (_v2485 == _v237)) || (_v2485 == _v238)));
}

bkr_bool _v2480(_v2411 _v2424, _v426 _v542, bkr_bool _v2472) {
    _v2471(_v2424, _v743(_v542), BKR_TRUE);
    _v436 _v621 = _v746(_v542);
    _v434 _v976 = _v749(_v542);
    _v435 _v977 = _v751(_v542);
    bkr_i64 _v2359 = _v2443(_v2424);
    bkr_i64 _v2486 = _v2443(_v2424);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        _v2445(_v2424, _v2359);
        bkr_i64 _v2441 = _v2439(_v2424);
        _v433 _v473 = _v925(_v621, _v1172);
        _v2481(_v2424, _v473, _v547(_v542));
        _v2487(_v2424, _v473);
        if ((_v1172 < _v916(_v977))) {
            bkr_i64 _v2488 = _v918(_v977, _v1172);
            if ((_v2488 != 0)) {
                _v2471(_v2424, _v2488, BKR_TRUE);
            }
        }
        if ((_v1172 < _v907(_v976))) {
            bkr_i64 _v379 = _v910(_v976, _v1172);
            _v341 _v2489 = _v507(_v379);
            if ((_v510(_v2489) == _v227)) {
                _v429 _v583 = _v579(_v379);
                if ((_v2472 && (!_v2484(_v583)))) {
                    _v2425(_v2424, "match_arm_missing_value", bkr_str_concat("match arm ", int_to_string((_v1172 + 1))), _v2489, "a block ending in a value expression", "a block without a final value", "End the arm block with the value the match should produce.");
                }
                _v2479(_v2424, _v583);
            } else {
                _v2471(_v2424, _v379, _v2472);
            }
        }
        _v2440(_v2424, _v2441);
        _v2446(_v2424, _v2486);
        _v1172 = (_v1172 + 1);
    }
    return _v2445(_v2424, _v2486);
}

bkr_bool _v2487(_v2411 _v2424, _v433 _v473) {
    bkr_i64 _v319 = _v597(_v473);
    bkr_i64 _v387 = _v598(_v473);
    if ((_v319 == _v285)) {
        return _v2437(_v2424, _v2423(_v2424, _v387), "", BKR_TRUE);
    }
    if ((((_v319 == _v287) || (_v319 == _v290)) || (_v319 == _v291))) {
        if ((_v387 >= 0)) {
            _v2437(_v2424, _v2423(_v2424, _v387), "", BKR_TRUE);
        }
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            return _v2487(_v2424, _v592(_v345));
        }
        return BKR_TRUE;
    }
    if ((((_v319 == _v289) || (_v319 == _v293)) || (_v319 == _v292))) {
        if ((_v600(_v473) >= 0)) {
            _v2437(_v2424, _v2423(_v2424, _v600(_v473)), "", BKR_TRUE);
        }
        if ((_v601(_v473) >= 0)) {
            _v2437(_v2424, _v2423(_v2424, _v601(_v473)), "", BKR_TRUE);
        }
    }
    return BKR_TRUE;
}

bkr_bool _v2479(_v2411 _v2424, _v429 _v583) {
    bkr_i64 _v2441 = _v2439(_v2424);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v590(_v583))) {
        _v2490(_v2424, _v1111(_v583, _v1172));
        _v1172 = (_v1172 + 1);
    }
    return _v2440(_v2424, _v2441);
}

bkr_bool _v2490(_v2411 _v2424, _v427 _v554) {
    bkr_i64 _v319 = _v556(_v554);
    if ((_v319 == _v228)) {
        bkr_str _v1363 = _v2423(_v2424, _v758(_v554));
        bkr_i64 _v366 = _v764(_v554);
        bkr_str _v2432 = _v2430(_v2424, _v761(_v554));
        if (_v526(_v366)) {
            _v2471(_v2424, _v366, BKR_TRUE);
            _v2469(_v2424, _v2432, _v366);
            if ((bkr_len((bkr_str)(intptr_t)(_v2432)) == 0)) {
                _v2432 = _v2448(_v2424, _v538(_v366));
            }
            _v2456(_v2424, _v366);
        }
        return _v2437(_v2424, _v1363, _v2432, (_v1066(_v554) || (!_v526(_v366))));
    }
    if ((_v319 == _v233)) {
        _v426 _v1098 = _v538(_v855(_v554));
        bkr_i64 _v387 = _v858(_v554);
        _v2471(_v2424, _v387, BKR_TRUE);
        if ((_v545(_v1098) == _v245)) {
            bkr_str _v1363 = _v2423(_v2424, _v663(_v1098));
            bkr_i64 _v1172 = _v2436(_v2424, _v1363);
            _v2456(_v2424, _v387);
            if ((_v1172 >= 0)) {
                if ((vec_get(_v2424._v2421, _v1172) == 0)) {
                    _v2425(_v2424, "immutable_assignment", _v1363, _v547(_v1098), "a variable declared with let mut", "immutable binding", bkr_str_concat(bkr_str_concat("Declare it as `let mut ", _v1363), "` to allow reassignment."));
                }
                vec_set(_v2424._v2422, _v1172, 0);
            }
            return BKR_TRUE;
        }
        _v2456(_v2424, _v387);
        return _v2473(_v2424, _v1098, BKR_TRUE);
    }
    if ((_v319 == _v229)) {
        return _v2471(_v2424, _v769(_v554), BKR_TRUE);
    }
    if ((_v319 == _v232)) {
        return _v2471(_v2424, _v861(_v554), BKR_FALSE);
    }
    if ((_v319 == _v230)) {
        _v2471(_v2424, _v828(_v554), BKR_TRUE);
        bkr_i64 _v2359 = _v2443(_v2424);
        _v2479(_v2424, _v830(_v554));
        bkr_i64 _v2486 = _v2443(_v2424);
        bkr_i64 _v2491 = _v833(_v554);
        if (_v526(_v2491)) {
            _v2445(_v2424, _v2359);
            _v2479(_v2424, _v579(_v2491));
            _v2446(_v2424, _v2486);
        }
        return _v2445(_v2424, _v2486);
    }
    if ((_v319 == _v231)) {
        _v2471(_v2424, _v850(_v554), BKR_TRUE);
        return _v2479(_v2424, _v852(_v554));
    }
    if ((_v319 == _v237)) {
        return _v2479(_v2424, _v847(_v554));
    }
    if ((_v319 == _v236)) {
        _v2471(_v2424, _v838(_v554), BKR_TRUE);
        _v2471(_v2424, _v841(_v554), BKR_TRUE);
        bkr_i64 _v2441 = _v2439(_v2424);
        _v2437(_v2424, _v2423(_v2424, _v835(_v554)), "i", BKR_TRUE);
        _v2479(_v2424, _v845(_v554));
        return _v2440(_v2424, _v2441);
    }
    if ((_v319 == _v238)) {
        return _v2490(_v2424, _v550(_v773(_v554)));
    }
    if ((_v319 == _v227)) {
        return _v2479(_v2424, _v579(_v553(_v554)));
    }
    return BKR_TRUE;
}

bkr_str _v2492(_v2411 _v2424, bkr_str _v2037, _v341 _v1523) {
    bkr_str _v2432 = _v2430(_v2424, _v866(_v1523));
    if (((bkr_len((bkr_str)(intptr_t)(_v2432)) == 0) && bkr_str_eq(_v2423(_v2424, _v863(_v1523)), "self"))) {
        bkr_i64 _v2493 = bkr_str_index_of((bkr_str)(intptr_t)(_v2037), (bkr_str)(intptr_t)("::"));
        if (((_v2493 > 0) && hashmap_contains(_v2424._v2416, ((bkr_i64)(intptr_t)substring(_v2037, 0, _v2493))))) {
            return bkr_str_concat("S:", substring(_v2037, 0, _v2493));
        }
    }
    return _v2432;
}

_v2411 _v2494(bkr_i64 _v425, bkr_str _v1212) {
    bkr_i64 _v2015 = vec_new();
    vec_push(_v2015, ((bkr_i64)(intptr_t)""));
    return (_v2411){._v425 = _v425, ._v1212 = _v1212, ._v2412 = _v1960(), ._v2015 = _v2015, ._v2413 = hashmap_new(), ._v2415 = hashmap_new(), ._v2416 = hashmap_new(), ._v2417 = hashmap_new(), ._v2418 = hashmap_new(), ._v2419 = vec_new(), ._v2420 = vec_new(), ._v2421 = vec_new(), ._v2422 = vec_new()};
}

bkr_i64 _v2496(_v341 _v1546, bkr_str _v1212) {
    _v2411 _v2424 = _v2494(_v904(_v1546), _v1212);
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v399 = _v907(_v1186);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v399)) {
        _v428 _v563 = _v914(_v1186, _v1172);
        bkr_i64 _v319 = _v569(_v563);
        if ((_v319 == _v254)) {
            hashmap_insert_str(_v2424._v2416, ((bkr_i64)(intptr_t)_v2423(_v2424, _v887(_v563))), 1);
        } else {
            if ((_v319 == _v259)) {
                bkr_str _v1642 = _v2423(_v2424, _v1168(_v563));
                hashmap_insert_str(_v2424._v2413, ((bkr_i64)(intptr_t)_v1642), 1);
                _v435 _v1166 = _v1169(_v563);
                _v435 _v1167 = _v1170(_v563);
                bkr_i64 _v1915 = 0;
                while ((_v1915 < _v916(_v1166))) {
                    bkr_i64 _v2482 = 0;
                    if ((_v1915 < _v916(_v1167))) {
                        bkr_i64 _v344 = _v918(_v1167, _v1915);
                        if ((_v344 != 0)) {
                            _v2482 = _v916(_v611(_v344));
                        }
                    }
                    hashmap_insert_str(_v2424._v2415, ((bkr_i64)(intptr_t)bkr_str_concat(bkr_str_concat(_v1642, "."), _v2423(_v2424, _v918(_v1166, _v1915)))), _v2482);
                    _v1915 = (_v1915 + 1);
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    _v1172 = 0;
    while ((_v1172 < _v399)) {
        _v428 _v563 = _v914(_v1186, _v1172);
        bkr_i64 _v319 = _v569(_v563);
        if ((_v319 == _v254)) {
            bkr_str _v1697 = _v2423(_v2424, _v887(_v563));
            _v434 _v1162 = _v890(_v563);
            bkr_i64 _v2498 = 0;
            while ((_v2498 < _v907(_v1162))) {
                _v341 _v1447 = _v913(_v1162, _v2498);
                hashmap_insert_str(_v2424._v2417, ((bkr_i64)(intptr_t)bkr_str_concat(bkr_str_concat(_v1697, "."), _v2423(_v2424, _v892(_v1447)))), ((bkr_i64)(intptr_t)_v2428(_v2424, _v896(_v1447))));
                _v2498 = (_v2498 + 1);
            }
        } else {
            if ((_v319 == _v224)) {
                hashmap_insert_str(_v2424._v2418, ((bkr_i64)(intptr_t)_v2423(_v2424, _v869(_v563))), ((bkr_i64)(intptr_t)_v2430(_v2424, _v875(_v563))));
            }
        }
        _v1172 = (_v1172 + 1);
    }
    _v1172 = 0;
    while ((_v1172 < _v399)) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if ((_v569(_v563) == _v224)) {
            bkr_str _v2037 = _v2423(_v2424, _v869(_v563));
            vec_set(_v2424._v2015, 0, ((bkr_i64)(intptr_t)bkr_str_concat("fn:", _v2037)));
            _v2440(_v2424, 0);
            _v434 _v1145 = _v872(_v563);
            bkr_i64 _v1261 = 0;
            while ((_v1261 < _v907(_v1145))) {
                _v341 _v1523 = _v913(_v1145, _v1261);
                _v2437(_v2424, _v2423(_v2424, _v863(_v1523)), _v2492(_v2424, _v2037, _v1523), BKR_TRUE);
                _v1261 = (_v1261 + 1);
            }
            _v2479(_v2424, _v877(_v563));
        }
        _v1172 = (_v1172 + 1);
    }
    return _v2424._v2412;
}

bkr_str _v2499(bkr_i64 _v0, bkr_str _v1212) {
    bkr_str _v1955 = ",";
    bkr_i64 _v2412 = _v2496(_v477(_v0), _v1212);
    bkr_i64 _v399 = _v1963(_v2412);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_SEMANTIC_JSON: {", _v1907("schema_version", "bunker.self_host.semantic.v1")), _v1955), _v1909("has_diagnostics", (_v399 > 0))), _v1955), _v1908("diagnostic_count", _v399)), _v1955), _v1908("error_count", _v399)), _v1955), _v1910("diagnostics", _v1961(_v2412))), "}"), from_char_code(10)), "*/"), from_char_code(10));
}

_v2502 _v2513(bkr_i64 _v2510) {
    bkr_i64 _v2503 = vec_new();
    bkr_i64 _v2504 = vec_new();
    bkr_i64 _v2505 = vec_new();
    bkr_i64 _v2506 = vec_new();
    bkr_i64 _v2507 = vec_new();
    bkr_i64 _v2511 = hashmap_new_str();
    bkr_i64 _v2512 = hashmap_new_str();
    return (_v2502){._v2503 = _v2503, ._v2504 = _v2504, ._v2505 = _v2505, ._v2506 = _v2506, ._v2507 = _v2507, ._v2508 = 0, ._v2509 = 0, ._v2510 = _v2510, ._v2374 = BKR_FALSE, ._v2511 = _v2511, ._v2512 = _v2512};
}

bkr_bool _v2514(_v2502 _v2515, bkr_str _v1363) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v2515._v2503))) {
        if (bkr_str_eq(vec_get(_v2515._v2503, _v1172), _v1363)) {
            return BKR_FALSE;
        }
        _v1172 = (_v1172 + 1);
    }
    vec_push(_v2515._v2503, ((bkr_i64)(intptr_t)_v1363));
    return BKR_TRUE;
}

bkr_str _v2516(bkr_str _v2517, bkr_str _v1841) {
    return bkr_str_concat(bkr_str_concat(_v2517, "."), _v1841);
}

bkr_bool _v2518(_v2502 _v2515, bkr_str _v2517, bkr_str _v1841, bkr_i64 _v1398) {
    bkr_str _v2519 = _v2516(_v2517, _v1841);
    return hashmap_insert_str(_v2515._v2511, ((bkr_i64)(intptr_t)_v2519), _v1398);
}

bkr_i64 _v2520(_v2502 _v2515, bkr_str _v2517, bkr_str _v1841) {
    bkr_str _v2519 = _v2516(_v2517, _v1841);
    if ((!hashmap_contains(_v2515._v2511, ((bkr_i64)(intptr_t)_v2519)))) {
        return 0;
    }
    return hashmap_get(_v2515._v2511, ((bkr_i64)(intptr_t)_v2519));
}

bkr_bool _v2521(_v2502 _v2515, bkr_str _v2517, bkr_str _v1841, bkr_str _v1398) {
    bkr_str _v2519 = _v2516(_v2517, _v1841);
    return hashmap_insert_str(_v2515._v2512, ((bkr_i64)(intptr_t)_v2519), ((bkr_i64)(intptr_t)_v1398));
}

bkr_str _v2522(_v2502 _v2515, bkr_str _v2517, bkr_str _v1841) {
    bkr_str _v2519 = _v2516(_v2517, _v1841);
    if ((!hashmap_contains(_v2515._v2512, ((bkr_i64)(intptr_t)_v2519)))) {
        return "";
    }
    return hashmap_get(_v2515._v2512, ((bkr_i64)(intptr_t)_v2519));
}

bkr_bool _v2523(_v2502 _v2515, bkr_str _v386, bkr_str _v1212, bkr_str _v2501, bkr_i64 _v344) {
    vec_push(_v2515._v2504, ((bkr_i64)(intptr_t)_v386));
    vec_push(_v2515._v2505, ((bkr_i64)(intptr_t)_v1212));
    vec_push(_v2515._v2506, ((bkr_i64)(intptr_t)_v2501));
    vec_push(_v2515._v2507, _v344);
    return BKR_TRUE;
}

bkr_i64 _v2524(_v2502 _v2515) {
    bkr_i64 _v2525 = vec_len(_v2515._v2506);
    if ((_v2515._v2508 >= _v2525)) {
        return 0;
    }
    return (_v2525 - _v2515._v2508);
}

bkr_bool _v2526(_v2502 _v2515) {
    return (_v2524(_v2515) > 0);
}

_v2500 _v2527(_v2502 _v2515) {
    if ((!_v2526(_v2515))) {
        return (_v2500){._v386 = "", ._v1212 = "", ._v2501 = "", ._v344 = 0};
    }
    bkr_i64 _v386 = vec_get(_v2515._v2504, _v2515._v2508);
    bkr_i64 _v1212 = vec_get(_v2515._v2505, _v2515._v2508);
    bkr_i64 _v2501 = vec_get(_v2515._v2506, _v2515._v2508);
    bkr_i64 _v344 = vec_get(_v2515._v2507, _v2515._v2508);
    _v2515._v2508 = (_v2515._v2508 + 1);
    return (_v2500){._v386 = _v386, ._v1212 = _v1212, ._v2501 = _v2501, ._v344 = _v344};
}

bkr_bool _v2528(_v2502 _v2515) {
    _v2515._v2374 = BKR_TRUE;
    return BKR_TRUE;
}

bkr_bool _v2529(_v2502 _v2515) {
    return _v2515._v2374;
}

bkr_i64 _v2530(_v2502 _v2515) {
    _v2515._v2509 = (_v2515._v2509 + 1);
    return _v2515._v2509;
}

bkr_str _v2531(_v2502 _v2515) {
    bkr_str _v1955 = ",";
    bkr_str _v2532 = "RUNNING";
    if (_v2515._v2374) {
        _v2532 = "COMPLETED";
    }
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.shell.v1")), _v1955), _v1907("status", _v2532)), _v1955), _v1908("steps_executed", _v2515._v2509)), _v1955), _v1908("max_steps", _v2515._v2510)), _v1955), _v1909("terminated", _v2515._v2374)), _v1955), _v1908("active_agents", vec_len(_v2515._v2503))), _v1955), _v1908("queue_depth", _v2524(_v2515))), "}");
}

_v2533 _v2548(bkr_str _v1363) {
    bkr_i64 _v2549 = vec_new();
    bkr_i64 _v2550 = vec_new();
    bkr_i64 _v2551 = vec_new();
    bkr_i64 _v2552 = vec_new();
    bkr_i64 _v2553 = vec_new();
    bkr_i64 _v2554 = vec_new();
    bkr_i64 _v2555 = vec_new();
    bkr_i64 _v2556 = vec_new();
    bkr_i64 _v2557 = vec_new();
    bkr_i64 _v2558 = vec_new();
    bkr_i64 _v2559 = vec_new();
    bkr_i64 _v2560 = vec_new();
    bkr_i64 _v2561 = vec_new();
    return (_v2533){._v2534 = _v2549, ._v2535 = _v2550, ._v2536 = _v2551, ._v2537 = _v2552, ._v2538 = _v2553, ._v2539 = _v2554, ._v2540 = _v2555, ._v2541 = _v2556, ._v2542 = _v2557, ._v2543 = _v2558, ._v2544 = _v2559, ._v2545 = _v2560, ._v2546 = _v2561, ._v2547 = (-1), ._v1363 = _v1363};
}

bkr_i64 _v2562(_v2533 _v2563, bkr_str _v319) {
    bkr_i64 _v1621 = vec_len(_v2563._v2534);
    vec_push(_v2563._v2534, ((bkr_i64)(intptr_t)_v319));
    vec_push(_v2563._v2535, ((bkr_i64)(intptr_t)""));
    vec_push(_v2563._v2536, ((bkr_i64)(intptr_t)""));
    vec_push(_v2563._v2537, 0);
    vec_push(_v2563._v2538, 0);
    vec_push(_v2563._v2539, 0);
    vec_push(_v2563._v2540, 0);
    vec_push(_v2563._v2541, 14);
    vec_push(_v2563._v2542, ((bkr_i64)(intptr_t)""));
    vec_push(_v2563._v2543, ((bkr_i64)(intptr_t)""));
    vec_push(_v2563._v2544, ((bkr_i64)(intptr_t)""));
    vec_push(_v2563._v2545, ((bkr_i64)(intptr_t)""));
    vec_push(_v2563._v2546, (-1));
    if ((_v2563._v2547 < 0)) {
        _v2563._v2547 = _v1621;
    }
    return _v1621;
}

bkr_bool _v2564(_v2533 _v2563, bkr_i64 _v2565, bkr_i64 _v2566) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v2565 < 0) || (_v2565 >= _v2525))) {
        return BKR_FALSE;
    }
    if (((_v2566 < 0) || (_v2566 >= _v2525))) {
        return BKR_FALSE;
    }
    vec_set(_v2563._v2546, _v2566, _v2565);
    return BKR_TRUE;
}

bkr_bool _v2567(_v2533 _v2563, bkr_i64 _v1621, bkr_str _v2568) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v1621 < 0) || (_v1621 >= _v2525))) {
        return BKR_FALSE;
    }
    vec_set(_v2563._v2535, _v1621, ((bkr_i64)(intptr_t)_v2568));
    return BKR_TRUE;
}

bkr_bool _v2569(_v2533 _v2563, bkr_i64 _v1621, bkr_i64 _v2570, bkr_i64 _v2571) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v1621 < 0) || (_v1621 >= _v2525))) {
        return BKR_FALSE;
    }
    vec_set(_v2563._v2537, _v1621, _v2570);
    vec_set(_v2563._v2538, _v1621, _v2571);
    return BKR_TRUE;
}

bkr_bool _v2572(_v2533 _v2563, bkr_i64 _v1621, bkr_str _v1305) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v1621 < 0) || (_v1621 >= _v2525))) {
        return BKR_FALSE;
    }
    vec_set(_v2563._v2536, _v1621, ((bkr_i64)(intptr_t)_v1305));
    return BKR_TRUE;
}

bkr_bool _v2573(_v2533 _v2563, bkr_i64 _v1621, bkr_i64 _v2574) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v1621 < 0) || (_v1621 >= _v2525))) {
        return BKR_FALSE;
    }
    vec_set(_v2563._v2539, _v1621, _v2574);
    return BKR_TRUE;
}

bkr_bool _v2575(_v2533 _v2563, bkr_i64 _v1621, bkr_i64 _v2576) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v1621 < 0) || (_v1621 >= _v2525))) {
        return BKR_FALSE;
    }
    vec_set(_v2563._v2540, _v1621, _v2576);
    return BKR_TRUE;
}

bkr_bool _v2577(_v2533 _v2563, bkr_i64 _v1621, bkr_i64 _v2578) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v1621 < 0) || (_v1621 >= _v2525))) {
        return BKR_FALSE;
    }
    vec_set(_v2563._v2541, _v1621, _v2578);
    return BKR_TRUE;
}

bkr_bool _v2579(_v2533 _v2563, bkr_i64 _v1621, bkr_str _v2517, bkr_str _v1841) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v1621 < 0) || (_v1621 >= _v2525))) {
        return BKR_FALSE;
    }
    vec_set(_v2563._v2542, _v1621, ((bkr_i64)(intptr_t)_v2517));
    vec_set(_v2563._v2543, _v1621, ((bkr_i64)(intptr_t)_v1841));
    return BKR_TRUE;
}

bkr_bool _v2580(_v2533 _v2563, bkr_i64 _v1621, bkr_str _v386, bkr_str _v2501) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v1621 < 0) || (_v1621 >= _v2525))) {
        return BKR_FALSE;
    }
    vec_set(_v2563._v2544, _v1621, ((bkr_i64)(intptr_t)_v386));
    vec_set(_v2563._v2545, _v1621, ((bkr_i64)(intptr_t)_v2501));
    return BKR_TRUE;
}

bkr_str _v2581(_v2533 _v2563, bkr_i64 _v1621) {
    if (((_v1621 < 0) || (_v1621 >= vec_len(_v2563._v2534)))) {
        return "";
    }
    return vec_get(_v2563._v2534, _v1621);
}

bkr_str _v2582(_v2533 _v2563, bkr_i64 _v1621) {
    if (((_v1621 < 0) || (_v1621 >= vec_len(_v2563._v2535)))) {
        return "";
    }
    return vec_get(_v2563._v2535, _v1621);
}

bkr_i64 _v2583(_v2533 _v2563, bkr_i64 _v1621) {
    if (((_v1621 < 0) || (_v1621 >= vec_len(_v2563._v2537)))) {
        return 0;
    }
    return vec_get(_v2563._v2537, _v1621);
}

bkr_i64 _v2584(_v2533 _v2563, bkr_i64 _v1621) {
    if (((_v1621 < 0) || (_v1621 >= vec_len(_v2563._v2538)))) {
        return 0;
    }
    return vec_get(_v2563._v2538, _v1621);
}

bkr_i64 _v2585(_v2533 _v2563, bkr_i64 _v1621) {
    if (((_v1621 < 0) || (_v1621 >= vec_len(_v2563._v2539)))) {
        return 0;
    }
    return vec_get(_v2563._v2539, _v1621);
}

bkr_str _v2586(_v2533 _v2563, bkr_i64 _v1621) {
    if (((_v1621 < 0) || (_v1621 >= vec_len(_v2563._v2536)))) {
        return "";
    }
    return vec_get(_v2563._v2536, _v1621);
}

bkr_str _v2587(_v2533 _v2563, bkr_i64 _v1621) {
    if (((_v1621 < 0) || (_v1621 >= vec_len(_v2563._v2544)))) {
        return "";
    }
    return vec_get(_v2563._v2544, _v1621);
}

bkr_str _v2588(_v2533 _v2563, bkr_i64 _v1621) {
    if (((_v1621 < 0) || (_v1621 >= vec_len(_v2563._v2545)))) {
        return "";
    }
    return vec_get(_v2563._v2545, _v1621);
}

bkr_str _v2589(_v2533 _v2563, bkr_i64 _v1621, _v2502 _v2515) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v1621 < 0) || (_v1621 >= _v2525))) {
        return "";
    }
    bkr_i64 _v2590 = vec_get(_v2563._v2542, _v1621);
    bkr_i64 _v2591 = vec_get(_v2563._v2543, _v1621);
    if (((bkr_len((bkr_str)(intptr_t)(_v2590)) > 0) && (bkr_len((bkr_str)(intptr_t)(_v2591)) > 0))) {
        bkr_i64 _v2592 = _v2520(_v2515, _v2590, _v2591);
        bkr_i64 _v1600 = vec_get(_v2563._v2536, _v1621);
        if ((bkr_len((bkr_str)(intptr_t)(_v1600)) > 0)) {
            return bkr_str_concat(_v1600, int_to_string(_v2592));
        }
        return int_to_string(_v2592);
    }
    return vec_get(_v2563._v2536, _v1621);
}

bkr_bool _v2593(_v2533 _v2563, bkr_i64 _v1621, _v2502 _v2515) {
    bkr_i64 _v2525 = vec_len(_v2563._v2534);
    if (((_v1621 < 0) || (_v1621 >= _v2525))) {
        return BKR_FALSE;
    }
    bkr_i64 _v386 = vec_get(_v2563._v2544, _v1621);
    bkr_i64 _v2501 = vec_get(_v2563._v2545, _v1621);
    if (((bkr_len((bkr_str)(intptr_t)(_v386)) > 0) && (bkr_len((bkr_str)(intptr_t)(_v2501)) > 0))) {
        return _v2523(_v2515, _v386, "View", _v2501, 0);
    }
    return BKR_FALSE;
}

bkr_str _v2594(_v2533 _v2563) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.view.v1")), _v1955), _v1907("view_name", _v2563._v1363)), _v1955), _v1908("component_count", vec_len(_v2563._v2534))), _v1955), _v1908("root_id", _v2563._v2547)), "}");
}

_v2595 _v2606(void) {
    bkr_i64 _v425 = vec_new();
    bkr_i64 _v2607 = vec_new();
    return (_v2595){._v2596 = _v425, ._v2597 = _v2607, ._v2598 = 0};
}

_v2595 _v2608(bkr_i64 _v1208) {
    bkr_i64 _v425 = vec_new();
    bkr_i64 _v2607 = vec_new();
    return (_v2595){._v2596 = _v425, ._v2597 = _v2607, ._v2598 = _v1208};
}

_v2595 _v2609(bkr_str _v1363) {
    bkr_i64 _v425 = vec_new();
    bkr_i64 _v2607 = vec_new();
    vec_push(_v425, ((bkr_i64)(intptr_t)_v1363));
    vec_push(_v2607, 1);
    return (_v2595){._v2596 = _v425, ._v2597 = _v2607, ._v2598 = 0};
}

_v2595 _v2610(bkr_str _v1363, bkr_i64 _v2611) {
    bkr_i64 _v425 = vec_new();
    bkr_i64 _v2607 = vec_new();
    vec_push(_v425, ((bkr_i64)(intptr_t)_v1363));
    vec_push(_v2607, _v2611);
    return (_v2595){._v2596 = _v425, ._v2597 = _v2607, ._v2598 = 0};
}

bkr_i64 _v2612(_v2595 _v368, bkr_str _v1363) {
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2525 = vec_len(_v368._v2596);
    while ((_v1172 < _v2525)) {
        if (bkr_str_eq(vec_get(_v368._v2596, _v1172), _v1363)) {
            return vec_get(_v368._v2597, _v1172);
        }
        _v1172 = (_v1172 + 1);
    }
    return 0;
}

bkr_bool _v2613(_v2595 _v368, bkr_str _v1363, bkr_i64 _v2611) {
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2525 = vec_len(_v368._v2596);
    while ((_v1172 < _v2525)) {
        if (bkr_str_eq(vec_get(_v368._v2596, _v1172), _v1363)) {
            vec_set(_v368._v2597, _v1172, _v2611);
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    vec_push(_v368._v2596, ((bkr_i64)(intptr_t)_v1363));
    vec_push(_v368._v2597, _v2611);
    return BKR_TRUE;
}

_v2595 _v2614(_v2595 _v2615, _v2595 _v2616) {
    _v2595 _v1733 = _v2606();
    _v1733._v2598 = (_v2615._v2598 + _v2616._v2598);
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2617 = vec_len(_v2615._v2596);
    while ((_v1172 < _v2617)) {
        bkr_i64 _v1363 = vec_get(_v2615._v2596, _v1172);
        bkr_i64 _v2611 = vec_get(_v2615._v2597, _v1172);
        _v2613(_v1733, _v1363, _v2611);
        _v1172 = (_v1172 + 1);
    }
    bkr_i64 _v1645 = 0;
    bkr_i64 _v2618 = vec_len(_v2616._v2596);
    while ((_v1645 < _v2618)) {
        bkr_i64 _v1363 = vec_get(_v2616._v2596, _v1645);
        bkr_i64 _v2611 = vec_get(_v2616._v2597, _v1645);
        bkr_i64 _v2619 = _v2612(_v1733, _v1363);
        _v2613(_v1733, _v1363, (_v2619 + _v2611));
        _v1645 = (_v1645 + 1);
    }
    return _v1733;
}

_v2595 _v2620(_v2595 _v2615, _v2595 _v2616) {
    _v2595 _v1733 = _v2606();
    _v1733._v2598 = (_v2615._v2598 - _v2616._v2598);
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2617 = vec_len(_v2615._v2596);
    while ((_v1172 < _v2617)) {
        bkr_i64 _v1363 = vec_get(_v2615._v2596, _v1172);
        bkr_i64 _v2611 = vec_get(_v2615._v2597, _v1172);
        _v2613(_v1733, _v1363, _v2611);
        _v1172 = (_v1172 + 1);
    }
    bkr_i64 _v1645 = 0;
    bkr_i64 _v2618 = vec_len(_v2616._v2596);
    while ((_v1645 < _v2618)) {
        bkr_i64 _v1363 = vec_get(_v2616._v2596, _v1645);
        bkr_i64 _v2611 = vec_get(_v2616._v2597, _v1645);
        bkr_i64 _v2619 = _v2612(_v1733, _v1363);
        _v2613(_v1733, _v1363, (_v2619 - _v2611));
        _v1645 = (_v1645 + 1);
    }
    return _v1733;
}

_v2595 _v2621(_v2595 _v2615, bkr_i64 _v574) {
    _v2595 _v1733 = _v2606();
    _v1733._v2598 = (_v2615._v2598 * _v574);
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2617 = vec_len(_v2615._v2596);
    while ((_v1172 < _v2617)) {
        bkr_i64 _v1363 = vec_get(_v2615._v2596, _v1172);
        bkr_i64 _v2611 = vec_get(_v2615._v2597, _v1172);
        _v2613(_v1733, _v1363, (_v2611 * _v574));
        _v1172 = (_v1172 + 1);
    }
    return _v1733;
}

bkr_bool _v2622(_v2595 _v368) {
    if ((_v368._v2598 != 0)) {
        return BKR_FALSE;
    }
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2525 = vec_len(_v368._v2596);
    while ((_v1172 < _v2525)) {
        if ((vec_get(_v368._v2597, _v1172) != 0)) {
            return BKR_FALSE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_TRUE;
}

bkr_i64 _v2623(_v2595 _v368, bkr_i64 _v2624) {
    bkr_i64 _v2447 = _v368._v2598;
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2525 = vec_len(_v368._v2596);
    while ((_v1172 < _v2525)) {
        bkr_i64 _v1363 = vec_get(_v368._v2596, _v1172);
        bkr_i64 _v2611 = vec_get(_v368._v2597, _v1172);
        if (hashmap_contains(_v2624, _v1363)) {
            bkr_i64 _v1398 = hashmap_get(_v2624, _v1363);
            _v2447 = (_v2447 + (_v2611 * _v1398));
        }
        _v1172 = (_v1172 + 1);
    }
    return _v2447;
}

bkr_str _v2625(_v2595 _v368) {
    bkr_str _v1856 = "";
    bkr_bool _v2466 = BKR_TRUE;
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2525 = vec_len(_v368._v2596);
    while ((_v1172 < _v2525)) {
        bkr_i64 _v2611 = vec_get(_v368._v2597, _v1172);
        bkr_i64 _v1363 = vec_get(_v368._v2596, _v1172);
        if ((_v2611 != 0)) {
            if (_v2466) {
                if ((_v2611 == 1)) {
                    _v1856 = bkr_str_concat(_v1856, _v1363);
                } else {
                    if ((_v2611 == (-1))) {
                        _v1856 = bkr_str_concat(bkr_str_concat(_v1856, "-"), _v1363);
                    } else {
                        _v1856 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1856, int_to_string(_v2611)), "*"), _v1363);
                    }
                }
                _v2466 = BKR_FALSE;
            } else {
                if ((_v2611 > 0)) {
                    _v1856 = bkr_str_concat(_v1856, " + ");
                    if ((_v2611 == 1)) {
                        _v1856 = bkr_str_concat(_v1856, _v1363);
                    } else {
                        _v1856 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1856, int_to_string(_v2611)), "*"), _v1363);
                    }
                } else {
                    _v1856 = bkr_str_concat(_v1856, " - ");
                    bkr_i64 _v2626 = (0 - _v2611);
                    if ((_v2626 == 1)) {
                        _v1856 = bkr_str_concat(_v1856, _v1363);
                    } else {
                        _v1856 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1856, int_to_string(_v2626)), "*"), _v1363);
                    }
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    if (((_v368._v2598 != 0) || _v2466)) {
        if (_v2466) {
            _v1856 = bkr_str_concat(_v1856, int_to_string(_v368._v2598));
        } else {
            if ((_v368._v2598 > 0)) {
                _v1856 = bkr_str_concat(bkr_str_concat(_v1856, " + "), int_to_string(_v368._v2598));
            } else {
                _v1856 = bkr_str_concat(bkr_str_concat(_v1856, " - "), int_to_string((0 - _v368._v2598)));
            }
        }
    }
    return _v1856;
}

_v2599 _v2627(bkr_str _v2600) {
    bkr_i64 _v2628 = vec_new();
    bkr_i64 _v2629 = vec_new();
    return (_v2599){._v2600 = _v2600, ._v2601 = _v2628, ._v2602 = _v2629, ._v2603 = BKR_TRUE, ._v2604 = BKR_TRUE, ._v2605 = ""};
}

bkr_bool _v2630(_v2599 _v2631, bkr_str _v2432) {
    vec_push(_v2631._v2601, ((bkr_i64)(intptr_t)_v2432));
    return BKR_TRUE;
}

bkr_bool _v2632(_v2599 _v2631, bkr_str _v2432) {
    vec_push(_v2631._v2602, ((bkr_i64)(intptr_t)_v2432));
    return BKR_TRUE;
}

bkr_bool _v2633(_v2595 _v2634, _v2595 _v2635) {
    _v2595 _v2636 = _v2620(_v2634, _v2635);
    return _v2622(_v2636);
}

bkr_str _v2637(_v2595 _v2634, _v2595 _v2635, bkr_i64 _v2624) {
    _v2595 _v2636 = _v2620(_v2634, _v2635);
    bkr_i64 _v2638 = _v2623(_v2636, _v2624);
    bkr_str _v2639 = _v2625(_v2636);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("diff: ", _v2639), " (evaluated: "), int_to_string(_v2638)), ")");
}

bkr_str _v2640(_v2599 _v2631) {
    bkr_str _v1955 = ",";
    bkr_i64 _v2641 = (vec_len(_v2631._v2601) + vec_len(_v2631._v2602));
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.verify.v1")), _v1955), _v1907("function_name", _v2631._v2600)), _v1955), _v1908("contracts_checked", _v2641)), _v1955), _v1909("verified", _v2631._v2604)), _v1955), _v1907("counterexample", _v2631._v2605)), "}");
}

_v2642 _v2668(bkr_i64 _v425) {
    bkr_i64 _v2664 = vec_new();
    vec_push(_v2664, 0);
    vec_push(_v2664, 0);
    vec_push(_v2664, 0);
    vec_push(_v2664, 0);
    bkr_i64 _v2655 = vec_new();
    vec_push(_v2655, ((bkr_i64)(intptr_t)""));
    return (_v2642){._v1244 = vec_new(), ._v425 = _v425, ._v2643 = vec_new(), ._v2644 = hashmap_new(), ._v2645 = hashmap_new(), ._v2646 = vec_new(), ._v2647 = vec_new(), ._v1553 = vec_new(), ._v2648 = vec_new(), ._v1554 = vec_new(), ._v2418 = hashmap_new(), ._v2649 = hashmap_new(), ._v2416 = hashmap_new(), ._v2650 = vec_new(), ._v2651 = vec_new(), ._v2652 = vec_new(), ._v2653 = vec_new(), ._v2413 = hashmap_new(), ._v2654 = hashmap_new(), ._v2655 = _v2655, ._v2656 = vec_new(), ._v2657 = vec_new(), ._v2658 = hashmap_new(), ._v2659 = vec_new(), ._v2660 = vec_new(), ._v2661 = vec_new(), ._v2662 = vec_new(), ._v2663 = vec_new(), ._v2664 = _v2664};
}

bkr_str _v2669(_v2642 _v2424, bkr_i64 _v1036) {
    if (((_v1036 >= 0) && (_v1036 < vec_len(_v2424._v425)))) {
        return vec_get(_v2424._v425, _v1036);
    }
    return "";
}

bkr_str _v2670(bkr_i64 _v319) {
    if ((_v319 == _v254)) {
        return "struct";
    }
    if ((_v319 == _v259)) {
        return "enum";
    }
    if ((_v319 == _v260)) {
        return "type alias";
    }
    if ((_v319 == _v248)) {
        return "string literal";
    }
    if ((_v319 == _v251)) {
        return "float literal";
    }
    if ((_v319 == _v252)) {
        return "array literal";
    }
    if ((_v319 == _v239)) {
        return "array literal";
    }
    if ((_v319 == _v253)) {
        return "indexing";
    }
    if ((_v319 == _v256)) {
        return "field access";
    }
    if ((_v319 == _v257)) {
        return "struct literal";
    }
    if ((_v319 == _v258)) {
        return "match";
    }
    if ((_v319 == _v261)) {
        return "method call";
    }
    if ((_v319 == _v238)) {
        return "defer";
    }
    if ((_v319 == _v240)) {
        return "? operator";
    }
    if ((_v319 == _v227)) {
        return "block expression";
    }
    return bkr_str_concat("node kind ", int_to_string(_v319));
}

bkr_bool _v2671(_v2642 _v2424, bkr_str _v2501) {
    vec_push(_v2424._v2643, ((bkr_i64)(intptr_t)_v2501));
    return BKR_FALSE;
}

bkr_i64 _v2672(_v2642 _v2424) {
    return vec_len(_v2424._v1244);
}

bkr_bool _v2673(_v2642 _v2424, bkr_i64 _v2674) {
    vec_push(_v2424._v1244, (_v2674 & 255));
    return BKR_TRUE;
}

bkr_bool _v2675(_v2642 _v2424, bkr_i64 _v2615, bkr_i64 _v2616) {
    _v2673(_v2424, _v2615);
    return _v2673(_v2424, _v2616);
}

bkr_bool _v2676(_v2642 _v2424, bkr_i64 _v2615, bkr_i64 _v2616, bkr_i64 _v1208) {
    _v2673(_v2424, _v2615);
    _v2673(_v2424, _v2616);
    return _v2673(_v2424, _v1208);
}

bkr_bool _v2677(_v2642 _v2424, bkr_i64 _v387) {
    _v2673(_v2424, _v387);
    _v2673(_v2424, (_v387 >> 8));
    _v2673(_v2424, (_v387 >> 16));
    return _v2673(_v2424, (_v387 >> 24));
}

bkr_bool _v2678(_v2642 _v2424, bkr_i64 _v387) {
    _v2677(_v2424, _v387);
    return _v2677(_v2424, (_v387 >> 32));
}

bkr_bool _v2679(_v2642 _v2424, bkr_i64 _v1213, bkr_i64 _v387) {
    vec_set(_v2424._v1244, _v1213, (_v387 & 255));
    vec_set(_v2424._v1244, (_v1213 + 1), ((_v387 >> 8) & 255));
    vec_set(_v2424._v1244, (_v1213 + 2), ((_v387 >> 16) & 255));
    vec_set(_v2424._v1244, (_v1213 + 3), ((_v387 >> 24) & 255));
    return BKR_TRUE;
}

bkr_bool _v2680(_v2642 _v2424, bkr_i64 _v1213, bkr_i64 _v386) {
    return _v2679(_v2424, _v1213, (_v386 - (_v1213 + 4)));
}

bkr_bool _v2681(_v2642 _v2424, bkr_i64 _v387) {
    _v2675(_v2424, 72, 184);
    return _v2678(_v2424, _v387);
}

bkr_bool _v2682(_v2642 _v2424, bkr_i64 _v1289) {
    _v2676(_v2424, 72, 139, 133);
    return _v2677(_v2424, (0 - _v1289));
}

bkr_bool _v2683(_v2642 _v2424, bkr_i64 _v1289) {
    _v2676(_v2424, 72, 137, 133);
    return _v2677(_v2424, (0 - _v1289));
}

bkr_bool _v2684(_v2642 _v2424, bkr_i64 _v1289) {
    _v2676(_v2424, 72, 141, 133);
    return _v2677(_v2424, (0 - _v1289));
}

bkr_bool _v2685(_v2642 _v2424, bkr_i64 _v1289) {
    _v2676(_v2424, 72, 141, 149);
    return _v2677(_v2424, (0 - _v1289));
}

bkr_bool _v2686(_v2642 _v2424, bkr_i64 _v1289) {
    _v2676(_v2424, 72, 139, 149);
    return _v2677(_v2424, (0 - _v1289));
}

bkr_bool _v2687(_v2642 _v2424, bkr_i64 _v1226) {
    _v2676(_v2424, 72, 139, 128);
    return _v2677(_v2424, (_v1226 * 8));
}

bkr_bool _v2688(_v2642 _v2424, bkr_i64 _v387) {
    _v2675(_v2424, 72, 5);
    return _v2677(_v2424, _v387);
}

bkr_bool _v2689(_v2642 _v2424, bkr_i64 _v387) {
    _v2675(_v2424, 72, 185);
    _v2678(_v2424, _v387);
    return _v2676(_v2424, 72, 57, 200);
}

bkr_bool _v2690(_v2642 _v2424, bkr_i64 _v2691) {
    _v2676(_v2424, 72, 193, 248);
    return _v2673(_v2424, _v2691);
}

bkr_bool _v2692(_v2642 _v2424, bkr_i64 _v387) {
    _v2675(_v2424, 72, 37);
    return _v2677(_v2424, _v387);
}

bkr_bool _v2693(_v2642 _v2424, bkr_i64 _v2694) {
    bkr_i64 _v574 = 0;
    while ((_v574 < _v2694)) {
        _v2676(_v2424, 72, 139, 136);
        _v2677(_v2424, (_v574 * 8));
        _v2676(_v2424, 72, 137, 138);
        _v2677(_v2424, (_v574 * 8));
        _v574 = (_v574 + 1);
    }
    return BKR_TRUE;
}

bkr_i64 _v2695(_v2642 _v2424) {
    _v2675(_v2424, 15, 133);
    bkr_i64 _v1213 = _v2672(_v2424);
    _v2677(_v2424, 0);
    return _v1213;
}

bkr_bool _v2696(_v2642 _v2424) {
    return _v2673(_v2424, 80);
}

bkr_bool _v2697(_v2642 _v2424) {
    return _v2673(_v2424, 88);
}

bkr_bool _v2698(_v2642 _v2424) {
    return _v2673(_v2424, 89);
}

bkr_bool _v2699(_v2642 _v2424) {
    return _v2676(_v2424, 72, 133, 192);
}

bkr_bool _v2700(_v2642 _v2424, bkr_i64 _v2701) {
    _v2676(_v2424, 15, _v2701, 192);
    _v2675(_v2424, 72, 15);
    return _v2675(_v2424, 182, 192);
}

bkr_i64 _v2702(_v2642 _v2424) {
    _v2673(_v2424, 233);
    bkr_i64 _v1213 = _v2672(_v2424);
    _v2677(_v2424, 0);
    return _v1213;
}

bkr_i64 _v2703(_v2642 _v2424) {
    _v2699(_v2424);
    _v2675(_v2424, 15, 132);
    bkr_i64 _v1213 = _v2672(_v2424);
    _v2677(_v2424, 0);
    return _v1213;
}

bkr_i64 _v2704(_v2642 _v2424) {
    _v2699(_v2424);
    _v2675(_v2424, 15, 133);
    bkr_i64 _v1213 = _v2672(_v2424);
    _v2677(_v2424, 0);
    return _v1213;
}

bkr_bool _v2705(_v2642 _v2424, bkr_i64 _v386) {
    _v2673(_v2424, 233);
    bkr_i64 _v1213 = _v2672(_v2424);
    _v2677(_v2424, 0);
    return _v2680(_v2424, _v1213, _v386);
}

bkr_bool _v2706(_v2642 _v2424) {
    _v2676(_v2424, 72, 137, 236);
    _v2673(_v2424, 93);
    return _v2673(_v2424, 195);
}

bkr_i64 _v2707(_v2642 _v2424, bkr_i64 _v2694) {
    bkr_i64 _v1289 = (vec_get(_v2424._v2664, 0) + (8 * _v2694));
    vec_set(_v2424._v2664, 0, _v1289);
    if ((_v1289 > vec_get(_v2424._v2664, 1))) {
        vec_set(_v2424._v2664, 1, _v1289);
    }
    return _v1289;
}

bkr_i64 _v2708(_v2642 _v2424, bkr_str _v1363, bkr_i64 _v1289, bkr_str _v1679) {
    vec_push(_v2424._v1553, ((bkr_i64)(intptr_t)_v1363));
    vec_push(_v2424._v2648, _v1289);
    vec_push(_v2424._v1554, ((bkr_i64)(intptr_t)_v1679));
    return _v1289;
}

bkr_i64 _v2709(_v2642 _v2424, bkr_str _v1363) {
    return _v2708(_v2424, _v1363, _v2707(_v2424, 1), "");
}

bkr_i64 _v2710(_v2642 _v2424, bkr_str _v1363) {
    bkr_i64 _v1172 = (vec_len(_v2424._v1553) - 1);
    while ((_v1172 >= 0)) {
        if (bkr_str_eq(vec_get(_v2424._v1553, _v1172), _v1363)) {
            return _v1172;
        }
        _v1172 = (_v1172 - 1);
    }
    return (-1);
}

bkr_i64 _v2711(_v2642 _v2424, bkr_str _v1363) {
    bkr_i64 _v1172 = _v2710(_v2424, _v1363);
    if ((_v1172 < 0)) {
        return (-1);
    }
    return vec_get(_v2424._v2648, _v1172);
}

bkr_str _v2712(_v2642 _v2424, bkr_str _v1363) {
    bkr_i64 _v1172 = _v2710(_v2424, _v1363);
    if ((_v1172 < 0)) {
        return "";
    }
    return vec_get(_v2424._v1554, _v1172);
}

bkr_i64 _v2713(_v2642 _v2424) {
    return vec_len(_v2424._v1553);
}

bkr_bool _v2714(_v2642 _v2424, bkr_i64 _v2441) {
    while ((vec_len(_v2424._v1553) > _v2441)) {
        vec_pop(_v2424._v1553);
        vec_pop(_v2424._v2648);
        vec_pop(_v2424._v1554);
    }
    return BKR_TRUE;
}

bkr_bool _v2715(_v2642 _v2424, bkr_str _v1679) {
    return ((bkr_len((bkr_str)(intptr_t)(_v1679)) > 0) && (!starts_with(_v1679, "$")));
}

bkr_bool _v2716(_v2642 _v2424, bkr_str _v1679) {
    return bkr_str_eq(_v1679, "$str");
}

bkr_str _v2717(bkr_i64 _v319) {
    if ((_v319 == _v306)) {
        return "s";
    }
    return "i";
}

bkr_str _v2718(bkr_str _v1679, bkr_str _v1600, bkr_i64 _v362) {
    if (((!starts_with(_v1679, _v1600)) || (bkr_len((bkr_str)(intptr_t)(_v1679)) <= (bkr_len((bkr_str)(intptr_t)(_v1600)) + _v362)))) {
        return "";
    }
    if (bkr_str_eq(char_at(_v1679, (bkr_len((bkr_str)(intptr_t)(_v1600)) + _v362)), "s")) {
        return "$str";
    }
    return "";
}

bkr_bool _v2719(_v2642 _v2424, bkr_str _v1679) {
    return starts_with(_v1679, "[");
}

bkr_i64 _v2720(_v2642 _v2424, bkr_str _v1679) {
    return parse_int(substring(_v1679, 1, bkr_str_index_of((bkr_str)(intptr_t)(_v1679), (bkr_str)(intptr_t)("]"))));
}

bkr_str _v2721(_v2642 _v2424, bkr_str _v1679) {
    return substring(_v1679, (bkr_str_index_of((bkr_str)(intptr_t)(_v1679), (bkr_str)(intptr_t)("]")) + 1), bkr_len((bkr_str)(intptr_t)(_v1679)));
}

bkr_i64 _v2722(_v2642 _v2424, bkr_str _v1679) {
    if (((bkr_len((bkr_str)(intptr_t)(_v1679)) == 0) || starts_with(_v1679, "$"))) {
        return 1;
    }
    if (_v2719(_v2424, _v1679)) {
        return (_v2720(_v2424, _v1679) * _v2722(_v2424, _v2721(_v2424, _v1679)));
    }
    bkr_i64 _v2578 = hashmap_get(_v2424._v2649, ((bkr_i64)(intptr_t)_v1679));
    return _v2578;
}

bkr_str _v2723(_v2642 _v2424, _v346 _v521) {
    if (_v523(_v521)) {
        return "";
    }
    bkr_i64 _v319 = _v530(_v521);
    if ((_v319 == _v308)) {
        bkr_i64 _v954 = _v533(_v521);
        if (((_v954 == _v309) || (_v954 == _v308))) {
            _v2671(_v2424, "unsupported type: array of structs or arrays");
            return "";
        }
        return bkr_str_concat(bkr_str_concat("[", int_to_string(_v534(_v521))), "]");
    }
    if ((_v319 == _v309)) {
        bkr_str _v1363 = _v2669(_v2424, _v532(_v521));
        if (hashmap_contains(_v2424._v2416, ((bkr_i64)(intptr_t)_v1363))) {
            return _v1363;
        }
    }
    if ((_v319 == _v306)) {
        return "$str";
    }
    if ((_v319 == _v310)) {
        return bkr_str_concat("$vec:", _v2717(_v535(_v521)));
    }
    if ((_v319 == _v311)) {
        return bkr_str_concat(bkr_str_concat("$map:", _v2717(_v535(_v521))), _v2717(_v536(_v521)));
    }
    if ((_v319 == _v312)) {
        return bkr_str_concat("$opt:", _v2717(_v535(_v521)));
    }
    if ((_v319 == _v313)) {
        return bkr_str_concat(bkr_str_concat("$res:", _v2717(_v535(_v521))), _v2717(_v536(_v521)));
    }
    return "";
}

bkr_str _v2724(bkr_str _v1363) {
    if ((((((((((((bkr_str_eq(_v1363, "char_at") || bkr_str_eq(_v1363, "substring")) || bkr_str_eq(_v1363, "trim")) || bkr_str_eq(_v1363, "int_to_string")) || bkr_str_eq(_v1363, "from_char_code")) || bkr_str_eq(_v1363, "join_lines")) || bkr_str_eq(_v1363, "read_file")) || bkr_str_eq(_v1363, "arg_at")) || bkr_str_eq(_v1363, "str_replace")) || bkr_str_eq(_v1363, "str_to_upper")) || bkr_str_eq(_v1363, "str_to_lower")) || bkr_str_eq(_v1363, "str_repeat"))) {
        return "$str";
    }
    if (bkr_str_eq(_v1363, "str_split")) {
        return "$vec:s";
    }
    if (bkr_str_eq(_v1363, "env_get")) {
        return "$opt:s";
    }
    if ((bkr_str_eq(_v1363, "read_file_result") || bkr_str_eq(_v1363, "process_run"))) {
        return "$res:ss";
    }
    return "";
}

bkr_str _v2725(_v2642 _v2424, bkr_i64 _v342) {
    if ((!_v526(_v342))) {
        return "";
    }
    return _v2723(_v2424, _v517(_v342));
}

bkr_i64 _v2726(_v2642 _v2424, bkr_str _v1697, bkr_str _v1154) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v2424._v2650))) {
        if ((bkr_str_eq(vec_get(_v2424._v2650, _v1172), _v1697) && bkr_str_eq(vec_get(_v2424._v2651, _v1172), _v1154))) {
            return _v1172;
        }
        _v1172 = (_v1172 + 1);
    }
    return (-1);
}

bkr_i64 _v2727(_v2642 _v2424, bkr_str _v1697, bkr_i64 _v2728) {
    bkr_i64 _v2729 = 0;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v2424._v2650))) {
        if (bkr_str_eq(vec_get(_v2424._v2650, _v1172), _v1697)) {
            if ((_v2729 == _v2728)) {
                return _v1172;
            }
            _v2729 = (_v2729 + 1);
        }
        _v1172 = (_v1172 + 1);
    }
    return (-1);
}

bkr_i64 _v2730(_v2642 _v2424, bkr_str _v1363, bkr_i64 _v1365) {
    if (hashmap_contains(_v2424._v2649, ((bkr_i64)(intptr_t)_v1363))) {
        bkr_i64 _v2731 = hashmap_get(_v2424._v2649, ((bkr_i64)(intptr_t)_v1363));
        return _v2731;
    }
    if ((_v1365 > 64)) {
        _v2671(_v2424, bkr_str_concat("recursive struct layout: ", _v1363));
        return 1;
    }
    bkr_i64 _v2694 = 0;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v2424._v2650))) {
        if (bkr_str_eq(vec_get(_v2424._v2650, _v1172), _v1363)) {
            vec_set(_v2424._v2653, _v1172, _v2694);
            bkr_str _v2732 = (bkr_str)(intptr_t)(vec_get(_v2424._v2652, _v1172));
            if ((bkr_len((bkr_str)(intptr_t)(_v2732)) == 0)) {
                _v2694 = (_v2694 + 1);
            } else {
                if (_v2719(_v2424, _v2732)) {
                    _v2694 = (_v2694 + _v2722(_v2424, _v2732));
                } else {
                    _v2694 = (_v2694 + _v2730(_v2424, _v2732, (_v1365 + 1)));
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    if ((_v2694 == 0)) {
        _v2694 = 1;
    }
    hashmap_insert_str(_v2424._v2649, ((bkr_i64)(intptr_t)_v1363), _v2694);
    return _v2694;
}

bkr_str _v2733(_v2642 _v2424, _v426 _v542) {
    bkr_str _v2734 = _v2735(_v2424, _v695(_v542));
    return bkr_str_concat(bkr_str_concat(_v2734, "::"), _v2669(_v2424, _v697(_v542)));
}

bkr_str _v2736(_v2642 _v2424, bkr_str _v1363) {
    if (hashmap_contains(_v2424._v2418, ((bkr_i64)(intptr_t)_v1363))) {
        bkr_str _v1679 = (bkr_str)(intptr_t)(hashmap_get(_v2424._v2418, ((bkr_i64)(intptr_t)_v1363)));
        return _v1679;
    }
    return "";
}

bkr_str _v2735(_v2642 _v2424, _v426 _v542) {
    bkr_i64 _v319 = _v545(_v542);
    if ((_v319 == _v248)) {
        return "$str";
    }
    if ((_v319 == _v241)) {
        return _v2723(_v2424, _v517(_v783(_v542)));
    }
    if ((_v319 == _v242)) {
        bkr_i64 _v349 = _v672(_v542);
        if ((_v349 == _v161)) {
            bkr_str _v2737 = _v2735(_v2424, _v538(_v675(_v542)));
            bkr_str _v2738 = _v2735(_v2424, _v538(_v678(_v542)));
            if ((_v2716(_v2424, _v2737) || _v2716(_v2424, _v2738))) {
                return "$str";
            }
        }
        return "";
    }
    if ((_v319 == _v227)) {
        _v429 _v583 = _v579(_v541(_v542));
        bkr_i64 _v399 = _v590(_v583);
        if ((_v399 > 0)) {
            _v427 _v2739 = _v1111(_v583, (_v399 - 1));
            if ((_v556(_v2739) == _v232)) {
                return _v2735(_v2424, _v538(_v861(_v2739)));
            }
        }
        return "";
    }
    if ((_v319 == _v245)) {
        return _v2712(_v2424, _v2669(_v2424, _v663(_v542)));
    }
    if ((_v319 == _v257)) {
        return _v2669(_v2424, _v725(_v542));
    }
    if ((_v319 == _v244)) {
        bkr_str _v1363 = _v2669(_v2424, _v689(_v542));
        if (hashmap_contains(_v2424._v2416, ((bkr_i64)(intptr_t)_v1363))) {
            return _v1363;
        }
        if (hashmap_contains(_v2424._v2645, ((bkr_i64)(intptr_t)_v1363))) {
            return _v2736(_v2424, _v1363);
        }
        _v434 _v1016 = _v692(_v542);
        if ((_v907(_v1016) > 0)) {
            bkr_str _v2740 = _v2735(_v2424, _v538(_v910(_v1016, 0)));
            if ((bkr_str_eq(_v1363, "vec_get") || bkr_str_eq(_v1363, "vec_pop"))) {
                return _v2718(_v2740, "$vec:", 0);
            }
            if (bkr_str_eq(_v1363, "hashmap_get")) {
                return _v2718(_v2740, "$map:", 1);
            }
            if ((bkr_str_eq(_v1363, "hashmap_keys") && starts_with(_v2740, "$map:"))) {
                return bkr_str_concat("$vec:", substring(_v2740, 5, 6));
            }
            if ((bkr_str_eq(_v1363, "hashmap_values") && starts_with(_v2740, "$map:"))) {
                return bkr_str_concat("$vec:", substring(_v2740, 6, 7));
            }
        }
        return _v2724(_v1363);
    }
    if ((_v319 == _v261)) {
        return _v2736(_v2424, _v2733(_v2424, _v542));
    }
    if ((_v319 == _v256)) {
        bkr_str _v2741 = _v2735(_v2424, _v721(_v542));
        if ((bkr_len((bkr_str)(intptr_t)(_v2741)) == 0)) {
            return "";
        }
        bkr_i64 _v2498 = _v2726(_v2424, _v2741, _v2669(_v2424, _v723(_v542)));
        if ((_v2498 < 0)) {
            return "";
        }
        return vec_get(_v2424._v2652, _v2498);
    }
    if ((_v319 == _v250)) {
        return _v2735(_v2424, _v538(_v737(_v542)));
    }
    if ((_v319 == _v253)) {
        bkr_str _v2741 = _v2735(_v2424, _v538(_v712(_v542)));
        if (_v2719(_v2424, _v2741)) {
            return _v2721(_v2424, _v2741);
        }
        return "";
    }
    if ((_v319 == _v252)) {
        _v434 _v2478 = _v702(_v542);
        bkr_i64 _v399 = _v907(_v2478);
        bkr_str _v2742 = "";
        if ((_v399 > 0)) {
            _v2742 = _v2735(_v2424, _v538(_v910(_v2478, 0)));
        }
        return bkr_str_concat(bkr_str_concat(bkr_str_concat("[", int_to_string(_v399)), "]"), _v2742);
    }
    if ((_v319 == _v239)) {
        return bkr_str_concat(bkr_str_concat(bkr_str_concat("[", int_to_string(_v707(_v542))), "]"), _v2735(_v2424, _v705(_v542)));
    }
    if ((_v319 == _v258)) {
        _v434 _v976 = _v749(_v542);
        if ((_v907(_v976) > 0)) {
            bkr_i64 _v379 = _v910(_v976, 0);
            if ((_v510(_v507(_v379)) != _v227)) {
                return _v2735(_v2424, _v538(_v379));
            }
        }
    }
    return "";
}

bkr_bool _v2743(_v2642 _v2424, bkr_i64 _v342) {
    return _v2744(_v2424, _v538(_v342));
}

bkr_bool _v2744(_v2642 _v2424, _v426 _v542) {
    bkr_i64 _v319 = _v545(_v542);
    if ((_v319 == _v246)) {
        return _v2681(_v2424, _v666(_v542));
    }
    if ((_v319 == _v247)) {
        if ((_v666(_v542) == 1)) {
            return _v2681(_v2424, 1);
        }
        return _v2681(_v2424, 0);
    }
    if ((_v319 == _v245)) {
        bkr_str _v1363 = _v2669(_v2424, _v663(_v542));
        bkr_i64 _v1289 = _v2711(_v2424, _v1363);
        if ((_v1289 > 0)) {
            if (_v2715(_v2424, _v2712(_v2424, _v1363))) {
                return _v2684(_v2424, _v1289);
            }
            return _v2682(_v2424, _v1289);
        }
        if (bkr_str_eq(_v1363, "None")) {
            return _v2681(_v2424, 0);
        }
        if (hashmap_contains(_v2424._v2658, ((bkr_i64)(intptr_t)_v1363))) {
            bkr_i64 _v2459 = hashmap_get(_v2424._v2658, ((bkr_i64)(intptr_t)_v1363));
            return _v2743(_v2424, _v2459);
        }
        return _v2671(_v2424, bkr_str_concat("unknown name: ", _v1363));
    }
    if ((_v319 == _v248)) {
        _v2676(_v2424, 72, 141, 5);
        vec_push(_v2424._v2656, _v2672(_v2424));
        vec_push(_v2424._v2657, ((bkr_i64)(intptr_t)((bkr_str)(_v666(_v542)))));
        return _v2677(_v2424, 0);
    }
    if ((_v319 == _v241)) {
        _v346 _v1098 = _v517(_v783(_v542));
        bkr_i64 _v1803 = _v530(_v1098);
        if ((_v1803 == _v304)) {
            return _v2671(_v2424, "unsupported cast target: float");
        }
        return _v2743(_v2424, _v782(_v542));
    }
    if ((_v319 == _v243)) {
        bkr_i64 _v349 = _v682(_v542);
        _v2743(_v2424, _v685(_v542));
        if ((_v349 == _v162)) {
            return _v2676(_v2424, 72, 247, 216);
        }
        if ((_v349 == _v174)) {
            _v2699(_v2424);
            return _v2700(_v2424, 148);
        }
        return _v2671(_v2424, "unsupported unary operator");
    }
    if ((_v319 == _v242)) {
        return _v2745(_v2424, _v542);
    }
    if ((_v319 == _v250)) {
        _v2743(_v2424, _v734(_v542));
        bkr_i64 _v2746 = _v2703(_v2424);
        _v2743(_v2424, _v737(_v542));
        bkr_i64 _v2747 = _v2702(_v2424);
        _v2680(_v2424, _v2746, _v2672(_v2424));
        _v2743(_v2424, _v740(_v542));
        return _v2680(_v2424, _v2747, _v2672(_v2424));
    }
    if ((_v319 == _v244)) {
        return _v2748(_v2424, _v542);
    }
    if ((_v319 == _v261)) {
        bkr_i64 _v2749 = vec_new();
        vec_push(_v2749, _v694(_v542));
        _v434 _v1016 = _v699(_v542);
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v907(_v1016))) {
            vec_push(_v2749, _v910(_v1016, _v1172));
            _v1172 = (_v1172 + 1);
        }
        return _v2750(_v2424, _v2733(_v2424, _v542), _v2749);
    }
    if ((_v319 == _v256)) {
        _v426 _v1038 = _v721(_v542);
        bkr_str _v1154 = _v2669(_v2424, _v723(_v542));
        if ((_v545(_v1038) == _v245)) {
            bkr_str _v2476 = _v2669(_v2424, _v663(_v1038));
            if (((_v2711(_v2424, _v2476) < 0) && hashmap_contains(_v2424._v2413, ((bkr_i64)(intptr_t)_v2476)))) {
                bkr_str _v1841 = bkr_str_concat(bkr_str_concat(_v2476, "."), _v1154);
                if ((!hashmap_contains(_v2424._v2654, ((bkr_i64)(intptr_t)_v1841)))) {
                    return _v2671(_v2424, bkr_str_concat("unknown enum variant: ", _v1841));
                }
                bkr_i64 _v1690 = hashmap_get(_v2424._v2654, ((bkr_i64)(intptr_t)_v1841));
                return _v2681(_v2424, _v1690);
            }
        }
        bkr_str _v2741 = _v2735(_v2424, _v1038);
        if ((!_v2715(_v2424, _v2741))) {
            return _v2671(_v2424, bkr_str_concat("field access on a non-struct value: .", _v1154));
        }
        bkr_i64 _v2498 = _v2726(_v2424, _v2741, _v1154);
        if ((_v2498 < 0)) {
            return _v2671(_v2424, bkr_str_concat(bkr_str_concat(bkr_str_concat("unknown field ", _v2741), "."), _v1154));
        }
        _v2744(_v2424, _v1038);
        if (_v2715(_v2424, vec_get(_v2424._v2652, _v2498))) {
            return _v2688(_v2424, (vec_get(_v2424._v2653, _v2498) * 8));
        }
        return _v2687(_v2424, vec_get(_v2424._v2653, _v2498));
    }
    if ((_v319 == _v257)) {
        return _v2751(_v2424, _v542);
    }
    if ((_v319 == _v252)) {
        _v434 _v2478 = _v702(_v542);
        bkr_i64 _v399 = _v907(_v2478);
        bkr_str _v1679 = _v2735(_v2424, _v542);
        bkr_str _v2742 = _v2721(_v2424, _v1679);
        bkr_i64 _v2752 = _v2722(_v2424, _v2742);
        bkr_i64 _v361 = _v2707(_v2424, _v2722(_v2424, _v1679));
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v399)) {
            bkr_i64 _v2753 = (_v361 - ((8 * _v2752) * _v1172));
            _v2743(_v2424, _v910(_v2478, _v1172));
            if (_v2715(_v2424, _v2742)) {
                _v2685(_v2424, _v2753);
                _v2693(_v2424, _v2752);
            } else {
                _v2683(_v2424, _v2753);
            }
            _v1172 = (_v1172 + 1);
        }
        return _v2684(_v2424, _v361);
    }
    if ((_v319 == _v239)) {
        bkr_i64 _v399 = _v707(_v542);
        _v426 _v1001 = _v705(_v542);
        if (_v2715(_v2424, _v2735(_v2424, _v1001))) {
            return _v2671(_v2424, "repeat arrays of structs are not supported");
        }
        if ((_v399 <= 0)) {
            return _v2671(_v2424, "repeat array needs a positive length");
        }
        bkr_i64 _v361 = _v2707(_v2424, _v399);
        _v2744(_v2424, _v1001);
        _v2685(_v2424, _v361);
        _v2675(_v2424, 72, 185);
        _v2678(_v2424, _v399);
        bkr_i64 _v2754 = _v2672(_v2424);
        _v2676(_v2424, 72, 137, 2);
        _v2676(_v2424, 72, 131, 194);
        _v2673(_v2424, 8);
        _v2676(_v2424, 72, 255, 201);
        _v2675(_v2424, 15, 133);
        bkr_i64 _v2755 = _v2672(_v2424);
        _v2677(_v2424, 0);
        _v2680(_v2424, _v2755, _v2754);
        return _v2684(_v2424, _v361);
    }
    if ((_v319 == _v253)) {
        bkr_str _v2742 = _v2735(_v2424, _v542);
        if ((!_v2756(_v2424, _v542))) {
            return BKR_FALSE;
        }
        if (_v2715(_v2424, _v2742)) {
            return BKR_TRUE;
        }
        return _v2676(_v2424, 72, 139, 0);
    }
    if ((_v319 == _v258)) {
        return _v2757(_v2424, _v542);
    }
    if ((_v319 == _v227)) {
        return _v2758(_v2424, _v579(_v541(_v542)));
    }
    return _v2671(_v2424, bkr_str_concat("unsupported expression: ", _v2670(_v319)));
}

bkr_bool _v2745(_v2642 _v2424, _v426 _v542) {
    bkr_i64 _v349 = _v672(_v542);
    bkr_i64 _v350 = _v675(_v542);
    bkr_i64 _v351 = _v678(_v542);
    if ((_v349 == _v172)) {
        _v2743(_v2424, _v350);
        bkr_i64 _v2759 = _v2703(_v2424);
        _v2743(_v2424, _v351);
        _v2699(_v2424);
        _v2700(_v2424, 149);
        bkr_i64 _v2747 = _v2702(_v2424);
        _v2680(_v2424, _v2759, _v2672(_v2424));
        _v2681(_v2424, 0);
        return _v2680(_v2424, _v2747, _v2672(_v2424));
    }
    if ((_v349 == _v173)) {
        _v2743(_v2424, _v350);
        bkr_i64 _v2760 = _v2704(_v2424);
        _v2743(_v2424, _v351);
        _v2699(_v2424);
        _v2700(_v2424, 149);
        bkr_i64 _v2747 = _v2702(_v2424);
        _v2680(_v2424, _v2760, _v2672(_v2424));
        _v2681(_v2424, 1);
        return _v2680(_v2424, _v2747, _v2672(_v2424));
    }
    if ((((_v349 == _v166) || (_v349 == _v167)) || (_v349 == _v161))) {
        bkr_str _v2737 = _v2735(_v2424, _v538(_v350));
        bkr_str _v2738 = _v2735(_v2424, _v538(_v351));
        if ((_v2716(_v2424, _v2737) || _v2716(_v2424, _v2738))) {
            bkr_i64 _v2749 = vec_new();
            vec_push(_v2749, _v350);
            vec_push(_v2749, _v351);
            if ((_v349 == _v161)) {
                return _v2750(_v2424, "rt_str_concat", _v2749);
            }
            _v2750(_v2424, "rt_str_eq", _v2749);
            if ((_v349 == _v167)) {
                _v2676(_v2424, 72, 131, 240);
                _v2673(_v2424, 1);
            }
            return BKR_TRUE;
        }
    }
    _v2743(_v2424, _v350);
    _v2696(_v2424);
    _v2743(_v2424, _v351);
    _v2676(_v2424, 72, 137, 193);
    _v2697(_v2424);
    if ((_v349 == _v161)) {
        return _v2676(_v2424, 72, 1, 200);
    }
    if ((_v349 == _v162)) {
        return _v2676(_v2424, 72, 41, 200);
    }
    if ((_v349 == _v163)) {
        _v2676(_v2424, 72, 15, 175);
        return _v2673(_v2424, 193);
    }
    if (((_v349 == _v164) || (_v349 == _v165))) {
        _v2675(_v2424, 72, 153);
        _v2676(_v2424, 72, 247, 249);
        if ((_v349 == _v165)) {
            return _v2676(_v2424, 72, 137, 208);
        }
        return BKR_TRUE;
    }
    if ((_v349 == _v175)) {
        return _v2676(_v2424, 72, 33, 200);
    }
    if ((_v349 == _v176)) {
        return _v2676(_v2424, 72, 9, 200);
    }
    if ((_v349 == _v177)) {
        return _v2676(_v2424, 72, 49, 200);
    }
    if ((_v349 == _v178)) {
        return _v2676(_v2424, 72, 211, 224);
    }
    if ((_v349 == _v179)) {
        return _v2676(_v2424, 72, 211, 248);
    }
    bkr_i64 _v2701 = 0;
    if ((_v349 == _v166)) {
        _v2701 = 148;
    }
    if ((_v349 == _v167)) {
        _v2701 = 149;
    }
    if ((_v349 == _v168)) {
        _v2701 = 156;
    }
    if ((_v349 == _v171)) {
        _v2701 = 157;
    }
    if ((_v349 == _v170)) {
        _v2701 = 158;
    }
    if ((_v349 == _v169)) {
        _v2701 = 159;
    }
    if ((_v2701 == 0)) {
        return _v2671(_v2424, "unsupported binary operator");
    }
    _v2676(_v2424, 72, 57, 200);
    return _v2700(_v2424, _v2701);
}

bkr_bool _v2756(_v2642 _v2424, _v426 _v542) {
    _v426 _v1038 = _v538(_v712(_v542));
    bkr_str _v2741 = _v2735(_v2424, _v1038);
    if ((!_v2719(_v2424, _v2741))) {
        return _v2671(_v2424, "indexing is only supported on fixed arrays");
    }
    bkr_i64 _v399 = _v2720(_v2424, _v2741);
    bkr_i64 _v2761 = (8 * _v2722(_v2424, _v2721(_v2424, _v2741)));
    _v2744(_v2424, _v1038);
    _v2696(_v2424);
    _v2743(_v2424, _v715(_v542));
    _v2689(_v2424, _v399);
    _v2675(_v2424, 15, 130);
    bkr_i64 _v2762 = _v2672(_v2424);
    _v2677(_v2424, 0);
    _v2673(_v2424, 191);
    _v2677(_v2424, 101);
    _v2673(_v2424, 184);
    _v2677(_v2424, 60);
    _v2675(_v2424, 15, 5);
    _v2680(_v2424, _v2762, _v2672(_v2424));
    _v2676(_v2424, 72, 105, 200);
    _v2677(_v2424, _v2761);
    _v2697(_v2424);
    return _v2676(_v2424, 72, 1, 200);
}

bkr_bool _v2748(_v2642 _v2424, _v426 _v542) {
    bkr_str _v1363 = _v2669(_v2424, _v689(_v542));
    _v434 _v1016 = _v692(_v542);
    bkr_i64 _v2465 = _v907(_v1016);
    if (((bkr_str_eq(_v1363, "len") && (_v2465 == 1)) && (!hashmap_contains(_v2424._v2645, ((bkr_i64)(intptr_t)_v1363))))) {
        bkr_str _v2763 = _v2735(_v2424, _v538(_v910(_v1016, 0)));
        if (_v2719(_v2424, _v2763)) {
            return _v2681(_v2424, _v2720(_v2424, _v2763));
        }
    }
    if ((starts_with(_v1363, "__") && (!hashmap_contains(_v2424._v2645, ((bkr_i64)(intptr_t)_v1363))))) {
        return _v2764(_v2424, _v1363, _v1016);
    }
    if ((((bkr_str_eq(_v1363, "Ok") || bkr_str_eq(_v1363, "Err")) && (_v2465 == 1)) && (!hashmap_contains(_v2424._v2645, ((bkr_i64)(intptr_t)_v1363))))) {
        bkr_i64 _v2765 = vec_new();
        vec_push(_v2765, _v910(_v1016, 0));
        if (bkr_str_eq(_v1363, "Ok")) {
            return _v2750(_v2424, "rt_result_ok", _v2765);
        }
        return _v2750(_v2424, "rt_result_err", _v2765);
    }
    if ((bkr_str_eq(_v1363, "Some") && (_v2465 == 1))) {
        _v2743(_v2424, _v910(_v1016, 0));
        _v2676(_v2424, 72, 209, 224);
        _v2676(_v2424, 72, 131, 200);
        return _v2673(_v2424, 1);
    }
    if (hashmap_contains(_v2424._v2416, ((bkr_i64)(intptr_t)_v1363))) {
        bkr_i64 _v2694 = _v2722(_v2424, _v1363);
        bkr_i64 _v361 = _v2707(_v2424, _v2694);
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v2465)) {
            bkr_i64 _v2498 = _v2727(_v2424, _v1363, _v1172);
            if ((_v2498 < 0)) {
                return _v2671(_v2424, bkr_str_concat("too many fields for ", _v1363));
            }
            _v2766(_v2424, _v361, _v2498, _v910(_v1016, _v1172));
            _v1172 = (_v1172 + 1);
        }
        return _v2684(_v2424, _v361);
    }
    bkr_i64 _v2749 = vec_new();
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v2465)) {
        vec_push(_v2749, _v910(_v1016, _v1172));
        _v1172 = (_v1172 + 1);
    }
    if ((((!hashmap_contains(_v2424._v2645, ((bkr_i64)(intptr_t)_v1363))) && (_v2465 >= 2)) && (bkr_str_eq(_v1363, "hashmap_insert") || bkr_str_eq(_v1363, "vec_contains")))) {
        bkr_str _v2767 = _v2735(_v2424, _v538(_v910(_v1016, 1)));
        if (_v2716(_v2424, _v2767)) {
            return _v2750(_v2424, bkr_str_concat(bkr_str_concat("rt_", _v1363), "_str"), _v2749);
        }
    }
    return _v2750(_v2424, _v1363, _v2749);
}

bkr_bool _v2750(_v2642 _v2424, bkr_str _v2768, bkr_i64 _v2749) {
    bkr_str _v1363 = _v2768;
    if ((!hashmap_contains(_v2424._v2645, ((bkr_i64)(intptr_t)_v1363)))) {
        if (bkr_str_eq(_v1363, "strlen")) {
            _v1363 = "rt_strlen";
        } else {
            _v1363 = bkr_str_concat("rt_", _v2768);
        }
    }
    if ((!hashmap_contains(_v2424._v2645, ((bkr_i64)(intptr_t)_v1363)))) {
        return _v2671(_v2424, bkr_str_concat("unsupported call to builtin or unknown function: ", _v2768));
    }
    bkr_i64 _v2769 = hashmap_get(_v2424._v2645, ((bkr_i64)(intptr_t)_v1363));
    if ((_v2769 != vec_len(_v2749))) {
        return _v2671(_v2424, bkr_str_concat("wrong number of arguments to ", _v2768));
    }
    bkr_i64 _v2465 = vec_len(_v2749);
    bkr_str _v2770 = _v2736(_v2424, _v1363);
    bkr_i64 _v2771 = 0;
    if (_v2715(_v2424, _v2770)) {
        _v2771 = 1;
    }
    bkr_i64 _v2772 = vec_new();
    if ((_v2771 == 1)) {
        bkr_i64 _v2773 = _v2707(_v2424, 1);
        _v2684(_v2424, _v2707(_v2424, _v2722(_v2424, _v2770)));
        _v2683(_v2424, _v2773);
        vec_push(_v2772, _v2773);
    }
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v2465)) {
        _v2743(_v2424, vec_get(_v2749, _v1172));
        bkr_i64 _v2753 = _v2707(_v2424, 1);
        _v2683(_v2424, _v2753);
        vec_push(_v2772, _v2753);
        _v1172 = (_v1172 + 1);
    }
    bkr_i64 _v2525 = vec_len(_v2772);
    bkr_i64 _v2774 = 0;
    bkr_i64 _v574 = (_v2525 - 1);
    while ((_v574 >= 6)) {
        _v2675(_v2424, 255, 181);
        _v2677(_v2424, (0 - vec_get(_v2772, _v574)));
        _v2774 = (_v2774 + 1);
        _v574 = (_v574 - 1);
    }
    bkr_i64 _v2305 = 0;
    while (((_v2305 < _v2525) && (_v2305 < 6))) {
        _v2775(_v2424, _v2305, vec_get(_v2772, _v2305));
        _v2305 = (_v2305 + 1);
    }
    _v2673(_v2424, 232);
    vec_push(_v2424._v2646, _v2672(_v2424));
    vec_push(_v2424._v2647, ((bkr_i64)(intptr_t)_v1363));
    _v2677(_v2424, 0);
    if ((_v2774 > 0)) {
        _v2676(_v2424, 72, 129, 196);
        _v2677(_v2424, (8 * _v2774));
    }
    return BKR_TRUE;
}

bkr_bool _v2775(_v2642 _v2424, bkr_i64 _v2776, bkr_i64 _v1289) {
    if ((_v2776 == 0)) {
        _v2676(_v2424, 72, 139, 189);
    }
    if ((_v2776 == 1)) {
        _v2676(_v2424, 72, 139, 181);
    }
    if ((_v2776 == 2)) {
        _v2676(_v2424, 72, 139, 149);
    }
    if ((_v2776 == 3)) {
        _v2676(_v2424, 72, 139, 141);
    }
    if ((_v2776 == 4)) {
        _v2676(_v2424, 76, 139, 133);
    }
    if ((_v2776 == 5)) {
        _v2676(_v2424, 76, 139, 141);
    }
    return _v2677(_v2424, (0 - _v1289));
}

bkr_bool _v2764(_v2642 _v2424, bkr_str _v1363, _v434 _v1016) {
    bkr_i64 _v2465 = _v907(_v1016);
    if ((bkr_str_eq(_v1363, "__globals") && (_v2465 == 0))) {
        return _v2681(_v2424, _v2666);
    }
    if (((bkr_str_eq(_v1363, "__syscall") && (_v2465 >= 1)) && (_v2465 <= 7))) {
        bkr_i64 _v1172 = 0;
        while ((_v1172 < _v2465)) {
            _v2743(_v2424, _v910(_v1016, _v1172));
            _v2696(_v2424);
            _v1172 = (_v1172 + 1);
        }
        bkr_i64 _v2305 = (_v2465 - 1);
        while ((_v2305 >= 0)) {
            if ((_v2305 == 0)) {
                _v2673(_v2424, 88);
            }
            if ((_v2305 == 1)) {
                _v2673(_v2424, 95);
            }
            if ((_v2305 == 2)) {
                _v2673(_v2424, 94);
            }
            if ((_v2305 == 3)) {
                _v2673(_v2424, 90);
            }
            if ((_v2305 == 4)) {
                _v2675(_v2424, 65, 90);
            }
            if ((_v2305 == 5)) {
                _v2675(_v2424, 65, 88);
            }
            if ((_v2305 == 6)) {
                _v2675(_v2424, 65, 89);
            }
            _v2305 = (_v2305 - 1);
        }
        return _v2675(_v2424, 15, 5);
    }
    if (((bkr_str_eq(_v1363, "__load8") || bkr_str_eq(_v1363, "__load64")) && (_v2465 == 1))) {
        _v2743(_v2424, _v910(_v1016, 0));
        if (bkr_str_eq(_v1363, "__load8")) {
            _v2675(_v2424, 72, 15);
            return _v2675(_v2424, 182, 0);
        }
        return _v2676(_v2424, 72, 139, 0);
    }
    if (((bkr_str_eq(_v1363, "__store8") || bkr_str_eq(_v1363, "__store64")) && (_v2465 == 2))) {
        _v2743(_v2424, _v910(_v1016, 0));
        _v2696(_v2424);
        _v2743(_v2424, _v910(_v1016, 1));
        _v2698(_v2424);
        if (bkr_str_eq(_v1363, "__store8")) {
            return _v2675(_v2424, 136, 1);
        }
        return _v2676(_v2424, 72, 137, 1);
    }
    return _v2671(_v2424, bkr_str_concat("unknown intrinsic: ", _v1363));
}

bkr_bool _v2777(_v2642 _v2424, bkr_i64 _v2776) {
    if ((_v2776 == 0)) {
        return _v2673(_v2424, 95);
    }
    if ((_v2776 == 1)) {
        return _v2673(_v2424, 94);
    }
    if ((_v2776 == 2)) {
        return _v2673(_v2424, 90);
    }
    if ((_v2776 == 3)) {
        return _v2673(_v2424, 89);
    }
    if ((_v2776 == 4)) {
        return _v2675(_v2424, 65, 88);
    }
    return _v2675(_v2424, 65, 89);
}

bkr_bool _v2766(_v2642 _v2424, bkr_i64 _v361, bkr_i64 _v2498, bkr_i64 _v2459) {
    bkr_i64 _v2778 = (_v361 - (8 * vec_get(_v2424._v2653, _v2498)));
    bkr_str _v2732 = (bkr_str)(intptr_t)(vec_get(_v2424._v2652, _v2498));
    _v2743(_v2424, _v2459);
    if (_v2715(_v2424, _v2732)) {
        _v2685(_v2424, _v2778);
        return _v2693(_v2424, _v2722(_v2424, _v2732));
    }
    return _v2683(_v2424, _v2778);
}

bkr_bool _v2751(_v2642 _v2424, _v426 _v542) {
    bkr_str _v1363 = _v2669(_v2424, _v725(_v542));
    if ((!hashmap_contains(_v2424._v2416, ((bkr_i64)(intptr_t)_v1363)))) {
        return _v2671(_v2424, bkr_str_concat("unknown struct: ", _v1363));
    }
    bkr_i64 _v2694 = _v2722(_v2424, _v1363);
    bkr_i64 _v361 = _v2707(_v2424, _v2694);
    bkr_i64 _v403 = _v1006(_v542);
    if (_v526(_v403)) {
        _v2743(_v2424, _v403);
        _v2685(_v2424, _v361);
        _v2693(_v2424, _v2694);
    }
    _v435 _v1188 = _v728(_v542);
    _v434 _v615 = _v731(_v542);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v916(_v1188))) {
        bkr_str _v1154 = _v2669(_v2424, _v918(_v1188, _v1172));
        bkr_i64 _v2498 = _v2726(_v2424, _v1363, _v1154);
        if ((_v2498 < 0)) {
            return _v2671(_v2424, bkr_str_concat(bkr_str_concat(bkr_str_concat("unknown field ", _v1363), "."), _v1154));
        }
        _v2766(_v2424, _v361, _v2498, _v910(_v615, _v1172));
        _v1172 = (_v1172 + 1);
    }
    return _v2684(_v2424, _v361);
}

bkr_bool _v2758(_v2642 _v2424, _v429 _v583) {
    bkr_i64 _v2441 = _v2713(_v2424);
    bkr_i64 _v399 = _v590(_v583);
    bkr_bool _v2779 = BKR_FALSE;
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v399)) {
        _v427 _v554 = _v1111(_v583, _v1172);
        if (((_v1172 == (_v399 - 1)) && (_v556(_v554) == _v232))) {
            _v2743(_v2424, _v861(_v554));
            _v2779 = BKR_TRUE;
        } else {
            _v2780(_v2424, _v554);
        }
        _v1172 = (_v1172 + 1);
    }
    if ((!_v2779)) {
        _v2681(_v2424, 0);
    }
    return _v2714(_v2424, _v2441);
}

bkr_bool _v2781(_v2642 _v2424, bkr_i64 _v342) {
    if ((_v510(_v507(_v342)) == _v227)) {
        return _v2758(_v2424, _v579(_v342));
    }
    return _v2743(_v2424, _v342);
}

bkr_i64 _v2782(_v2642 _v2424, _v433 _v473) {
    bkr_str _v1841 = bkr_str_concat(bkr_str_concat(_v2669(_v2424, _v598(_v473)), "."), _v2669(_v2424, _v599(_v473)));
    if ((!hashmap_contains(_v2424._v2654, ((bkr_i64)(intptr_t)_v1841)))) {
        _v2671(_v2424, bkr_str_concat("unknown enum variant in pattern: ", _v1841));
        return (-1);
    }
    bkr_i64 _v1690 = hashmap_get(_v2424._v2654, ((bkr_i64)(intptr_t)_v1841));
    return _v1690;
}

bkr_i64 _v2783(_v2642 _v2424, bkr_i64 _v2753, bkr_i64 _v2691, bkr_i64 _v2784) {
    _v2682(_v2424, _v2753);
    if ((_v2691 > 0)) {
        _v2690(_v2424, _v2691);
    }
    if ((_v2784 > 0)) {
        _v2692(_v2424, _v2784);
    }
    bkr_i64 _v2785 = _v2707(_v2424, 1);
    _v2683(_v2424, _v2785);
    return _v2785;
}

bkr_bool _v2786(_v2642 _v2424, _v433 _v473, bkr_i64 _v2753, bkr_i64 _v2787) {
    bkr_i64 _v319 = _v597(_v473);
    bkr_i64 _v387 = _v598(_v473);
    if (((_v319 == _v285) || (_v319 == _v286))) {
        return BKR_TRUE;
    }
    if (((_v319 == _v283) || (_v319 == _v284))) {
        _v2682(_v2424, _v2753);
        bkr_i64 _v1279 = _v387;
        if (((_v319 == _v284) && (_v387 != 0))) {
            _v1279 = 1;
        }
        _v2689(_v2424, _v1279);
        vec_push(_v2787, _v2695(_v2424));
        return BKR_TRUE;
    }
    if ((_v319 == _v288)) {
        _v2682(_v2424, _v2753);
        vec_push(_v2787, _v2704(_v2424));
        return BKR_TRUE;
    }
    if ((_v319 == _v287)) {
        _v2682(_v2424, _v2753);
        _v2692(_v2424, 1);
        vec_push(_v2787, _v2703(_v2424));
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            bkr_i64 _v2013 = _v2783(_v2424, _v2753, 1, 0);
            return _v2786(_v2424, _v592(_v345), _v2013, _v2787);
        }
        return BKR_TRUE;
    }
    if (((_v319 == _v290) || (_v319 == _v291))) {
        _v2682(_v2424, _v2753);
        _v2676(_v2424, 72, 139, 0);
        if ((_v319 == _v290)) {
            _v2689(_v2424, 0);
        } else {
            _v2689(_v2424, 1);
        }
        vec_push(_v2787, _v2695(_v2424));
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            bkr_i64 _v2013 = _v2788(_v2424, _v2753);
            return _v2786(_v2424, _v592(_v345), _v2013, _v2787);
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v289)) {
        bkr_i64 _v1690 = _v2782(_v2424, _v473);
        _v2682(_v2424, _v2753);
        if ((_v600(_v473) >= 0)) {
            _v2692(_v2424, 255);
        }
        _v2689(_v2424, _v1690);
        vec_push(_v2787, _v2695(_v2424));
        return BKR_TRUE;
    }
    return _v2671(_v2424, bkr_str_concat("unsupported match pattern kind ", int_to_string(_v319)));
}

bkr_i64 _v2788(_v2642 _v2424, bkr_i64 _v2753) {
    _v2682(_v2424, _v2753);
    _v2687(_v2424, 1);
    bkr_i64 _v2785 = _v2707(_v2424, 1);
    _v2683(_v2424, _v2785);
    return _v2785;
}

bkr_bool _v2789(_v2642 _v2424, bkr_i64 _v355, bkr_i64 _v2753, bkr_i64 _v2691, bkr_i64 _v2784, bkr_str _v1679) {
    bkr_i64 _v2785 = _v2783(_v2424, _v2753, _v2691, _v2784);
    _v2708(_v2424, _v2669(_v2424, _v355), _v2785, _v1679);
    return BKR_TRUE;
}

bkr_bool _v2790(_v2642 _v2424, _v433 _v473, bkr_i64 _v2753, bkr_str _v1679) {
    bkr_i64 _v319 = _v597(_v473);
    bkr_i64 _v387 = _v598(_v473);
    if ((_v319 == _v285)) {
        return _v2789(_v2424, _v387, _v2753, 0, 0, _v1679);
    }
    if ((_v319 == _v287)) {
        bkr_str _v2791 = _v2718(_v1679, "$opt:", 0);
        if ((_v387 >= 0)) {
            _v2789(_v2424, _v387, _v2753, 1, 0, _v2791);
        }
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            bkr_i64 _v2013 = _v2783(_v2424, _v2753, 1, 0);
            return _v2790(_v2424, _v592(_v345), _v2013, _v2791);
        }
        return BKR_TRUE;
    }
    if (((_v319 == _v290) || (_v319 == _v291))) {
        bkr_i64 _v2792 = 0;
        if ((_v319 == _v291)) {
            _v2792 = 1;
        }
        bkr_str _v2791 = _v2718(_v1679, "$res:", _v2792);
        bkr_i64 _v2013 = _v2788(_v2424, _v2753);
        if ((_v387 >= 0)) {
            _v2708(_v2424, _v2669(_v2424, _v387), _v2013, _v2791);
        }
        bkr_i64 _v345 = _v599(_v473);
        if ((_v345 != 0)) {
            return _v2790(_v2424, _v592(_v345), _v2013, _v2791);
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v289)) {
        bkr_i64 _v431 = _v600(_v473);
        bkr_i64 _v432 = _v601(_v473);
        if (((_v431 >= 0) && (_v432 >= 0))) {
            _v2789(_v2424, _v431, _v2753, 20, 0, "");
            return _v2789(_v2424, _v432, _v2753, 8, 4095, "");
        }
        if ((_v431 >= 0)) {
            return _v2789(_v2424, _v431, _v2753, 8, 0, "");
        }
    }
    return BKR_TRUE;
}

bkr_bool _v2757(_v2642 _v2424, _v426 _v542) {
    _v426 _v975 = _v538(_v743(_v542));
    if (_v2715(_v2424, _v2735(_v2424, _v975))) {
        return _v2671(_v2424, "match on struct values is not supported");
    }
    bkr_str _v2793 = _v2735(_v2424, _v975);
    _v2744(_v2424, _v975);
    bkr_i64 _v2753 = _v2707(_v2424, 1);
    _v2683(_v2424, _v2753);
    _v436 _v621 = _v746(_v542);
    _v434 _v976 = _v749(_v542);
    _v435 _v977 = _v751(_v542);
    bkr_i64 _v2794 = vec_new();
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v920(_v621))) {
        bkr_i64 _v2441 = _v2713(_v2424);
        _v433 _v473 = _v925(_v621, _v1172);
        bkr_i64 _v2787 = vec_new();
        _v2786(_v2424, _v473, _v2753, _v2787);
        _v2790(_v2424, _v473, _v2753, _v2793);
        if ((_v1172 < _v916(_v977))) {
            bkr_i64 _v2488 = _v918(_v977, _v1172);
            if ((_v2488 != 0)) {
                _v2743(_v2424, _v2488);
                vec_push(_v2787, _v2703(_v2424));
            }
        }
        _v2781(_v2424, _v910(_v976, _v1172));
        vec_push(_v2794, _v2702(_v2424));
        bkr_i64 _v1218 = _v2672(_v2424);
        bkr_i64 _v1645 = 0;
        while ((_v1645 < vec_len(_v2787))) {
            _v2680(_v2424, vec_get(_v2787, _v1645), _v1218);
            _v1645 = (_v1645 + 1);
        }
        _v2714(_v2424, _v2441);
        _v1172 = (_v1172 + 1);
    }
    _v2681(_v2424, 0);
    bkr_i64 _v340 = _v2672(_v2424);
    bkr_i64 _v574 = 0;
    while ((_v574 < vec_len(_v2794))) {
        _v2680(_v2424, vec_get(_v2794, _v574), _v340);
        _v574 = (_v574 + 1);
    }
    return BKR_TRUE;
}

bkr_bool _v2795(_v2642 _v2424, _v429 _v583) {
    bkr_i64 _v2441 = _v2713(_v2424);
    bkr_i64 _v1172 = 0;
    bkr_i64 _v399 = _v590(_v583);
    while ((_v1172 < _v399)) {
        _v2780(_v2424, _v1111(_v583, _v1172));
        _v1172 = (_v1172 + 1);
    }
    return _v2714(_v2424, _v2441);
}

bkr_bool _v2796(_v2642 _v2424, bkr_i64 _v342, bkr_str _v1363) {
    _v426 _v542 = _v538(_v342);
    if ((_v545(_v542) != _v244)) {
        return BKR_FALSE;
    }
    return (bkr_str_eq(_v2669(_v2424, _v689(_v542)), _v1363) && (!hashmap_contains(_v2424._v2645, ((bkr_i64)(intptr_t)_v1363))));
}

bkr_i64 _v2797(_v2642 _v2424) {
    bkr_i64 _v1621 = vec_get(_v2424._v2664, 2);
    vec_set(_v2424._v2664, 2, (_v1621 + 1));
    vec_push(_v2424._v2663, _v1621);
    return _v1621;
}

bkr_bool _v2798(_v2642 _v2424, bkr_i64 _v2799, bkr_i64 _v2800, bkr_i64 _v1621, bkr_i64 _v386) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v2799))) {
        if ((vec_get(_v2800, _v1172) == _v1621)) {
            _v2680(_v2424, vec_get(_v2799, _v1172), _v386);
            vec_set(_v2800, _v1172, (-1));
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_TRUE;
}

bkr_bool _v2801(_v2642 _v2424, bkr_i64 _v1621, bkr_i64 _v2802, bkr_i64 _v2803) {
    _v2798(_v2424, _v2424._v2661, _v2424._v2662, _v1621, _v2802);
    _v2798(_v2424, _v2424._v2659, _v2424._v2660, _v1621, _v2803);
    vec_pop(_v2424._v2663);
    return BKR_TRUE;
}

bkr_i64 _v2804(_v2642 _v2424) {
    if ((vec_len(_v2424._v2663) == 0)) {
        return (-1);
    }
    return vec_get(_v2424._v2663, (vec_len(_v2424._v2663) - 1));
}

bkr_bool _v2780(_v2642 _v2424, _v427 _v554) {
    bkr_i64 _v319 = _v556(_v554);
    if ((_v319 == _v228)) {
        bkr_str _v1363 = _v2669(_v2424, _v758(_v554));
        bkr_i64 _v366 = _v764(_v554);
        bkr_str _v1679 = _v2725(_v2424, _v761(_v554));
        if (((bkr_len((bkr_str)(intptr_t)(_v1679)) == 0) && _v526(_v366))) {
            _v1679 = _v2735(_v2424, _v538(_v366));
        }
        if (((_v526(_v366) && starts_with(_v1679, "$map:s")) && _v2796(_v2424, _v366, "hashmap_new"))) {
            _v2750(_v2424, "rt_hashmap_new_str", vec_new());
        } else {
            if (_v526(_v366)) {
                _v2743(_v2424, _v366);
            } else {
                _v2681(_v2424, 0);
            }
        }
        if (_v2715(_v2424, _v1679)) {
            bkr_i64 _v2694 = _v2722(_v2424, _v1679);
            bkr_i64 _v578 = _v2707(_v2424, _v2694);
            if (_v526(_v366)) {
                _v2685(_v2424, _v578);
                _v2693(_v2424, _v2694);
            }
            _v2708(_v2424, _v1363, _v578, _v1679);
            return BKR_TRUE;
        }
        bkr_i64 _v1289 = _v2708(_v2424, _v1363, _v2707(_v2424, 1), _v1679);
        return _v2683(_v2424, _v1289);
    }
    if ((_v319 == _v233)) {
        _v426 _v1098 = _v538(_v855(_v554));
        bkr_i64 _v2459 = _v858(_v554);
        bkr_i64 _v1803 = _v545(_v1098);
        if ((_v1803 == _v256)) {
            _v426 _v1038 = _v721(_v1098);
            bkr_str _v2741 = _v2735(_v2424, _v1038);
            bkr_str _v1154 = _v2669(_v2424, _v723(_v1098));
            bkr_i64 _v2498 = _v2726(_v2424, _v2741, _v1154);
            if (((!_v2715(_v2424, _v2741)) || (_v2498 < 0))) {
                return _v2671(_v2424, bkr_str_concat("assignment to unknown field .", _v1154));
            }
            _v2744(_v2424, _v1038);
            _v2688(_v2424, (vec_get(_v2424._v2653, _v2498) * 8));
            _v2696(_v2424);
            _v2743(_v2424, _v2459);
            bkr_str _v2732 = (bkr_str)(intptr_t)(vec_get(_v2424._v2652, _v2498));
            if (_v2715(_v2424, _v2732)) {
                _v2673(_v2424, 90);
                return _v2693(_v2424, _v2722(_v2424, _v2732));
            }
            _v2698(_v2424);
            return _v2676(_v2424, 72, 137, 1);
        }
        if ((_v1803 == _v253)) {
            bkr_str _v2742 = _v2735(_v2424, _v1098);
            if ((!_v2756(_v2424, _v1098))) {
                return BKR_FALSE;
            }
            _v2696(_v2424);
            _v2743(_v2424, _v2459);
            if (_v2715(_v2424, _v2742)) {
                _v2673(_v2424, 90);
                return _v2693(_v2424, _v2722(_v2424, _v2742));
            }
            _v2698(_v2424);
            return _v2676(_v2424, 72, 137, 1);
        }
        if ((_v1803 != _v245)) {
            return _v2671(_v2424, "unsupported assignment target");
        }
        bkr_str _v1363 = _v2669(_v2424, _v663(_v1098));
        bkr_i64 _v1289 = _v2711(_v2424, _v1363);
        if ((_v1289 <= 0)) {
            return _v2671(_v2424, bkr_str_concat("assignment to unknown local: ", _v1363));
        }
        _v2743(_v2424, _v2459);
        bkr_str _v2805 = _v2712(_v2424, _v1363);
        if (_v2715(_v2424, _v2805)) {
            _v2685(_v2424, _v1289);
            return _v2693(_v2424, _v2722(_v2424, _v2805));
        }
        return _v2683(_v2424, _v1289);
    }
    if ((_v319 == _v229)) {
        bkr_i64 _v368 = _v769(_v554);
        if (_v526(_v368)) {
            _v2743(_v2424, _v368);
        } else {
            _v2681(_v2424, 0);
        }
        bkr_str _v2770 = (bkr_str)(intptr_t)(vec_get(_v2424._v2655, 0));
        if (_v2715(_v2424, _v2770)) {
            _v2686(_v2424, vec_get(_v2424._v2664, 3));
            _v2693(_v2424, _v2722(_v2424, _v2770));
            _v2676(_v2424, 72, 137, 208);
        }
        return _v2706(_v2424);
    }
    if ((_v319 == _v232)) {
        return _v2743(_v2424, _v861(_v554));
    }
    if ((_v319 == _v230)) {
        _v2743(_v2424, _v828(_v554));
        bkr_i64 _v2746 = _v2703(_v2424);
        _v2795(_v2424, _v830(_v554));
        bkr_i64 _v2491 = _v833(_v554);
        if (_v526(_v2491)) {
            bkr_i64 _v2747 = _v2702(_v2424);
            _v2680(_v2424, _v2746, _v2672(_v2424));
            _v2795(_v2424, _v579(_v2491));
            return _v2680(_v2424, _v2747, _v2672(_v2424));
        }
        return _v2680(_v2424, _v2746, _v2672(_v2424));
    }
    if ((_v319 == _v231)) {
        bkr_i64 _v1621 = _v2797(_v2424);
        bkr_i64 _v2754 = _v2672(_v2424);
        _v2743(_v2424, _v850(_v554));
        bkr_i64 _v2747 = _v2703(_v2424);
        _v2795(_v2424, _v852(_v554));
        _v2705(_v2424, _v2754);
        bkr_i64 _v340 = _v2672(_v2424);
        _v2680(_v2424, _v2747, _v340);
        return _v2801(_v2424, _v1621, _v2754, _v340);
    }
    if ((_v319 == _v237)) {
        bkr_i64 _v1621 = _v2797(_v2424);
        bkr_i64 _v2754 = _v2672(_v2424);
        _v2795(_v2424, _v847(_v554));
        _v2705(_v2424, _v2754);
        return _v2801(_v2424, _v1621, _v2754, _v2672(_v2424));
    }
    if ((_v319 == _v236)) {
        bkr_i64 _v2441 = _v2713(_v2424);
        bkr_str _v1363 = _v2669(_v2424, _v835(_v554));
        _v2743(_v2424, _v841(_v554));
        bkr_i64 _v2806 = _v2709(_v2424, "$for_end");
        _v2683(_v2424, _v2806);
        _v2743(_v2424, _v838(_v554));
        bkr_i64 _v2807 = _v2709(_v2424, _v1363);
        _v2683(_v2424, _v2807);
        bkr_i64 _v1621 = _v2797(_v2424);
        bkr_i64 _v2754 = _v2672(_v2424);
        _v2682(_v2424, _v2807);
        _v2676(_v2424, 72, 139, 141);
        _v2677(_v2424, (0 - _v2806));
        _v2676(_v2424, 72, 57, 200);
        if ((_v843(_v554) != 0)) {
            _v2675(_v2424, 15, 143);
        } else {
            _v2675(_v2424, 15, 141);
        }
        bkr_i64 _v2747 = _v2672(_v2424);
        _v2677(_v2424, 0);
        _v2795(_v2424, _v845(_v554));
        bkr_i64 _v2808 = _v2672(_v2424);
        _v2682(_v2424, _v2807);
        _v2676(_v2424, 72, 131, 192);
        _v2673(_v2424, 1);
        _v2683(_v2424, _v2807);
        _v2705(_v2424, _v2754);
        bkr_i64 _v340 = _v2672(_v2424);
        _v2680(_v2424, _v2747, _v340);
        _v2801(_v2424, _v1621, _v2808, _v340);
        return _v2714(_v2424, _v2441);
    }
    if (((_v319 == _v234) || (_v319 == _v235))) {
        bkr_i64 _v1621 = _v2804(_v2424);
        if ((_v1621 < 0)) {
            return _v2671(_v2424, "break or continue outside a loop");
        }
        bkr_i64 _v1213 = _v2702(_v2424);
        if ((_v319 == _v234)) {
            vec_push(_v2424._v2659, _v1213);
            vec_push(_v2424._v2660, _v1621);
        } else {
            vec_push(_v2424._v2661, _v1213);
            vec_push(_v2424._v2662, _v1621);
        }
        return BKR_TRUE;
    }
    if ((_v319 == _v227)) {
        return _v2795(_v2424, _v579(_v553(_v554)));
    }
    return _v2671(_v2424, bkr_str_concat("unsupported statement: ", _v2670(_v319)));
}

bkr_bool _v2809(_v2642 _v2424, bkr_i64 _v2776, bkr_i64 _v1289) {
    if ((_v2776 == 0)) {
        _v2676(_v2424, 72, 137, 189);
    }
    if ((_v2776 == 1)) {
        _v2676(_v2424, 72, 137, 181);
    }
    if ((_v2776 == 2)) {
        _v2676(_v2424, 72, 137, 149);
    }
    if ((_v2776 == 3)) {
        _v2676(_v2424, 72, 137, 141);
    }
    if ((_v2776 == 4)) {
        _v2676(_v2424, 76, 137, 133);
    }
    if ((_v2776 == 5)) {
        _v2676(_v2424, 76, 137, 141);
    }
    return _v2677(_v2424, (0 - _v1289));
}

bkr_str _v2810(_v2642 _v2424, bkr_str _v2037, _v341 _v1523) {
    bkr_str _v1679 = _v2725(_v2424, _v866(_v1523));
    if (((bkr_len((bkr_str)(intptr_t)(_v1679)) == 0) && bkr_str_eq(_v2669(_v2424, _v863(_v1523)), "self"))) {
        bkr_i64 _v2493 = bkr_str_index_of((bkr_str)(intptr_t)(_v2037), (bkr_str)(intptr_t)("::"));
        if ((_v2493 > 0)) {
            bkr_str _v2811 = substring(_v2037, 0, _v2493);
            if (hashmap_contains(_v2424._v2416, ((bkr_i64)(intptr_t)_v2811))) {
                return _v2811;
            }
        }
    }
    return _v1679;
}

bkr_bool _v2812(_v2642 _v2424, _v428 _v1530) {
    bkr_str _v1363 = _v2669(_v2424, _v869(_v1530));
    hashmap_insert_str(_v2424._v2644, ((bkr_i64)(intptr_t)_v1363), _v2672(_v2424));
    vec_set(_v2424._v2664, 0, 0);
    vec_set(_v2424._v2664, 1, 0);
    _v2714(_v2424, 0);
    _v2673(_v2424, 85);
    _v2676(_v2424, 72, 137, 229);
    _v2676(_v2424, 72, 129, 236);
    bkr_i64 _v2813 = _v2672(_v2424);
    _v2677(_v2424, 0);
    bkr_str _v2770 = _v2736(_v2424, _v1363);
    vec_set(_v2424._v2655, 0, ((bkr_i64)(intptr_t)_v2770));
    bkr_i64 _v2771 = 0;
    vec_set(_v2424._v2664, 3, 0);
    if (_v2715(_v2424, _v2770)) {
        _v2771 = 1;
        bkr_i64 _v2773 = _v2707(_v2424, 1);
        vec_set(_v2424._v2664, 3, _v2773);
        _v2809(_v2424, 0, _v2773);
    }
    _v434 _v1145 = _v872(_v1530);
    bkr_i64 _v399 = _v907(_v1145);
    bkr_i64 _v2814 = vec_new();
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v399)) {
        bkr_i64 _v2753 = _v2707(_v2424, 1);
        bkr_i64 _v2776 = (_v1172 + _v2771);
        if ((_v2776 < 6)) {
            _v2809(_v2424, _v2776, _v2753);
        } else {
            _v2676(_v2424, 72, 139, 133);
            _v2677(_v2424, (16 + (8 * (_v2776 - 6))));
            _v2683(_v2424, _v2753);
        }
        vec_push(_v2814, _v2753);
        _v1172 = (_v1172 + 1);
    }
    _v1172 = 0;
    while ((_v1172 < _v399)) {
        _v341 _v1523 = _v913(_v1145, _v1172);
        bkr_str _v1522 = _v2669(_v2424, _v863(_v1523));
        bkr_str _v2815 = _v2810(_v2424, _v1363, _v1523);
        bkr_i64 _v2753 = vec_get(_v2814, _v1172);
        if (_v2715(_v2424, _v2815)) {
            bkr_i64 _v2694 = _v2722(_v2424, _v2815);
            bkr_i64 _v578 = _v2707(_v2424, _v2694);
            _v2682(_v2424, _v2753);
            _v2685(_v2424, _v578);
            _v2693(_v2424, _v2694);
            _v2708(_v2424, _v1522, _v578, _v2815);
        } else {
            _v2708(_v2424, _v1522, _v2753, _v2815);
        }
        _v1172 = (_v1172 + 1);
    }
    _v2795(_v2424, _v877(_v1530));
    _v2681(_v2424, 0);
    _v2706(_v2424);
    bkr_i64 _v2816 = vec_get(_v2424._v2664, 1);
    _v2816 = (((_v2816 + 15) / 16) * 16);
    return _v2679(_v2424, _v2813, _v2816);
}

_v2642 _v2817(_v341 _v1546) {
    _v2642 _v2424 = _v2668(_v904(_v1546));
    _v434 _v1186 = _v899(_v1546);
    bkr_i64 _v2818 = _v907(_v1186);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < _v2818)) {
        _v428 _v563 = _v914(_v1186, _v1172);
        bkr_i64 _v1825 = _v569(_v563);
        if ((_v1825 == _v254)) {
            hashmap_insert_str(_v2424._v2416, ((bkr_i64)(intptr_t)_v2669(_v2424, _v887(_v563))), 1);
        } else {
            if ((_v1825 == _v259)) {
                bkr_str _v1642 = _v2669(_v2424, _v1168(_v563));
                hashmap_insert_str(_v2424._v2413, ((bkr_i64)(intptr_t)_v1642), 1);
                _v435 _v1166 = _v1169(_v563);
                bkr_i64 _v1915 = 0;
                while ((_v1915 < _v916(_v1166))) {
                    hashmap_insert_str(_v2424._v2654, ((bkr_i64)(intptr_t)bkr_str_concat(bkr_str_concat(_v1642, "."), _v2669(_v2424, _v918(_v1166, _v1915)))), _v1915);
                    _v1915 = (_v1915 + 1);
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    _v1172 = 0;
    while ((_v1172 < _v2818)) {
        _v428 _v563 = _v914(_v1186, _v1172);
        bkr_i64 _v1825 = _v569(_v563);
        if ((_v1825 == _v254)) {
            bkr_str _v1697 = _v2669(_v2424, _v887(_v563));
            _v434 _v1162 = _v890(_v563);
            bkr_i64 _v2498 = 0;
            while ((_v2498 < _v907(_v1162))) {
                _v341 _v1447 = _v913(_v1162, _v2498);
                vec_push(_v2424._v2650, ((bkr_i64)(intptr_t)_v1697));
                vec_push(_v2424._v2651, ((bkr_i64)(intptr_t)_v2669(_v2424, _v892(_v1447))));
                vec_push(_v2424._v2652, ((bkr_i64)(intptr_t)_v2723(_v2424, _v896(_v1447))));
                vec_push(_v2424._v2653, 0);
                _v2498 = (_v2498 + 1);
            }
        } else {
            if ((_v1825 == _v224)) {
                bkr_str _v2037 = _v2669(_v2424, _v869(_v563));
                if ((!hashmap_contains(_v2424._v2645, ((bkr_i64)(intptr_t)_v2037)))) {
                    hashmap_insert_str(_v2424._v2645, ((bkr_i64)(intptr_t)_v2037), _v907(_v872(_v563)));
                    hashmap_insert_str(_v2424._v2418, ((bkr_i64)(intptr_t)_v2037), ((bkr_i64)(intptr_t)_v2725(_v2424, _v875(_v563))));
                }
            } else {
                if ((_v1825 == _v249)) {
                    hashmap_insert_str(_v2424._v2658, ((bkr_i64)(intptr_t)_v2669(_v2424, _v879(_v563))), _v885(_v563));
                } else {
                    if ((_v1825 != _v259)) {
                        _v2671(_v2424, bkr_str_concat("unsupported top-level item: ", _v2670(_v1825)));
                    }
                }
            }
        }
        _v1172 = (_v1172 + 1);
    }
    bkr_i64 _v2819 = hashmap_keys(_v2424._v2416);
    bkr_i64 _v1902 = 0;
    while ((_v1902 < vec_len(_v2819))) {
        _v2730(_v2424, vec_get(_v2819, _v1902), 0);
        _v1902 = (_v1902 + 1);
    }
    bkr_str _v2821 = _v2669(_v2424, _v901(_v1546));
    if ((!hashmap_contains(_v2424._v2645, ((bkr_i64)(intptr_t)_v2821)))) {
        _v2671(_v2424, bkr_str_concat("missing entry function: ", _v2821));
        return _v2424;
    }
    _v2681(_v2424, _v2666);
    _v2676(_v2424, 72, 137, 32);
    _v2673(_v2424, 232);
    vec_push(_v2424._v2646, _v2672(_v2424));
    vec_push(_v2424._v2647, ((bkr_i64)(intptr_t)_v2821));
    _v2677(_v2424, 0);
    _v2676(_v2424, 72, 137, 199);
    _v2673(_v2424, 184);
    _v2677(_v2424, 60);
    _v2675(_v2424, 15, 5);
    _v1172 = 0;
    while ((_v1172 < _v2818)) {
        _v428 _v563 = _v914(_v1186, _v1172);
        if (((_v569(_v563) == _v224) && (!hashmap_contains(_v2424._v2644, ((bkr_i64)(intptr_t)_v2669(_v2424, _v869(_v563))))))) {
            _v2812(_v2424, _v563);
        }
        _v1172 = (_v1172 + 1);
    }
    bkr_i64 _v2498 = 0;
    while ((_v2498 < vec_len(_v2424._v2646))) {
        bkr_i64 _v386 = hashmap_get(_v2424._v2644, vec_get(_v2424._v2647, _v2498));
        _v2680(_v2424, vec_get(_v2424._v2646, _v2498), _v386);
        _v2498 = (_v2498 + 1);
    }
    bkr_i64 _v2822 = hashmap_new_str();
    bkr_i64 _v2823 = 0;
    while ((_v2823 < vec_len(_v2424._v2656))) {
        bkr_str _v1305 = (bkr_str)(intptr_t)(vec_get(_v2424._v2657, _v2823));
        if ((!hashmap_contains(_v2822, ((bkr_i64)(intptr_t)_v1305)))) {
            hashmap_insert_str(_v2822, ((bkr_i64)(intptr_t)_v1305), _v2672(_v2424));
            bkr_i64 _v1208 = 0;
            while ((_v1208 < bkr_len((bkr_str)(intptr_t)(_v1305)))) {
                _v2673(_v2424, char_code(char_at(_v1305, _v1208)));
                _v1208 = (_v1208 + 1);
            }
            _v2673(_v2424, 0);
        }
        bkr_i64 _v386 = hashmap_get(_v2822, ((bkr_i64)(intptr_t)_v1305));
        _v2680(_v2424, vec_get(_v2424._v2656, _v2823), _v386);
        _v2823 = (_v2823 + 1);
    }
    return _v2424;
}

bkr_bool _v2824(bkr_i64 _v1856, bkr_i64 _v387) {
    vec_push(_v1856, (_v387 & 255));
    vec_push(_v1856, ((_v387 >> 8) & 255));
    return BKR_TRUE;
}

bkr_bool _v2825(bkr_i64 _v1856, bkr_i64 _v387) {
    _v2824(_v1856, _v387);
    return _v2824(_v1856, (_v387 >> 16));
}

bkr_bool _v2826(bkr_i64 _v1856, bkr_i64 _v387) {
    _v2825(_v1856, _v387);
    return _v2825(_v1856, (_v387 >> 32));
}

bkr_i64 _v2827(bkr_i64 _v1244) {
    bkr_i64 _v1856 = vec_new();
    bkr_i64 _v2525 = (176 + vec_len(_v1244));
    vec_push(_v1856, 127);
    vec_push(_v1856, 69);
    vec_push(_v1856, 76);
    vec_push(_v1856, 70);
    vec_push(_v1856, 2);
    vec_push(_v1856, 1);
    vec_push(_v1856, 1);
    bkr_i64 _v2828 = 0;
    while ((_v2828 < 9)) {
        vec_push(_v1856, 0);
        _v2828 = (_v2828 + 1);
    }
    _v2824(_v1856, 2);
    _v2824(_v1856, 62);
    _v2825(_v1856, 1);
    _v2826(_v1856, _v2665);
    _v2826(_v1856, 64);
    _v2826(_v1856, 0);
    _v2825(_v1856, 0);
    _v2824(_v1856, 64);
    _v2824(_v1856, 56);
    _v2824(_v1856, 2);
    _v2824(_v1856, 0);
    _v2824(_v1856, 0);
    _v2824(_v1856, 0);
    _v2825(_v1856, 1);
    _v2825(_v1856, 5);
    _v2826(_v1856, 0);
    _v2826(_v1856, 4194304);
    _v2826(_v1856, 4194304);
    _v2826(_v1856, _v2525);
    _v2826(_v1856, _v2525);
    _v2826(_v1856, 4096);
    _v2825(_v1856, 1);
    _v2825(_v1856, 6);
    _v2826(_v1856, 0);
    _v2826(_v1856, _v2666);
    _v2826(_v1856, _v2666);
    _v2826(_v1856, 0);
    _v2826(_v1856, _v2667);
    _v2826(_v1856, 4096);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v1244))) {
        vec_push(_v1856, vec_get(_v1244, _v1172));
        _v1172 = (_v1172 + 1);
    }
    return _v1856;
}

bkr_bool _v2829(bkr_str _v2830, bkr_i64 _v2831) {
    bkr_i64 _v2832 = bytes_new(vec_len(_v2831));
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v2831))) {
        bytes_push(_v2832, ((bkr_i32)(vec_get(_v2831, _v1172))));
        _v1172 = (_v1172 + 1);
    }
    bkr_i64 _v1733 = file_write_bytes(_v2830, _v2832);
    if ((!bkr_result_is_ok(_v1733))) {
        return BKR_FALSE;
    }
    return file_set_executable(_v2830);
}

bkr_bool _v2839(bkr_str _v1598) {
    bkr_str _v2840 = trim(_v1598);
    bkr_i64 _v1902 = bkr_len((bkr_str)(intptr_t)(_v2840));
    if ((_v1902 < 11)) {
        return BKR_FALSE;
    }
    if ((!starts_with(_v2840, "import "))) {
        return BKR_FALSE;
    }
    if ((char_code_at(_v2840, 7) != 34)) {
        return BKR_FALSE;
    }
    if ((char_code_at(_v2840, (_v1902 - 2)) != 34)) {
        return BKR_FALSE;
    }
    if ((char_code_at(_v2840, (_v1902 - 1)) != 59)) {
        return BKR_FALSE;
    }
    return BKR_TRUE;
}

bkr_str _v2842(bkr_str _v1598) {
    bkr_str _v2840 = trim(_v1598);
    return substring(_v2840, 8, (bkr_len((bkr_str)(intptr_t)(_v2840)) - 2));
}

bkr_bool _v2843(bkr_str _v2844) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < bkr_len((bkr_str)(intptr_t)(_v2844)))) {
        if ((char_code_at(_v2844, _v1172) == 92)) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_bool _v2845(bkr_str _v2844) {
    if ((bkr_len((bkr_str)(intptr_t)(_v2844)) <= 0)) {
        return BKR_FALSE;
    }
    if ((char_code_at(_v2844, 0) == 47)) {
        return BKR_TRUE;
    }
    if ((char_code_at(_v2844, 0) == 92)) {
        return BKR_TRUE;
    }
    if (((bkr_len((bkr_str)(intptr_t)(_v2844)) >= 2) && (char_code_at(_v2844, 1) == 58))) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2846(bkr_str _v2844) {
    if (bkr_str_eq(_v2844, "..")) {
        return BKR_TRUE;
    }
    if (starts_with(_v2844, "../")) {
        return BKR_TRUE;
    }
    if (ends_with(_v2844, "/..")) {
        return BKR_TRUE;
    }
    if (contains(_v2844, "/../")) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2849(bkr_str _v2844) {
    if (starts_with(_v2844, "./")) {
        return BKR_TRUE;
    }
    if (ends_with(_v2844, "/")) {
        return BKR_TRUE;
    }
    if (contains(_v2844, "//")) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_bool _v2850(bkr_str _v2844) {
    if ((bkr_len((bkr_str)(intptr_t)(_v2844)) <= 0)) {
        return BKR_FALSE;
    }
    if (_v2845(_v2844)) {
        return BKR_FALSE;
    }
    if (_v2843(_v2844)) {
        return BKR_FALSE;
    }
    if (contains(_v2844, ":")) {
        return BKR_FALSE;
    }
    if (_v2846(_v2844)) {
        return BKR_FALSE;
    }
    if (_v2849(_v2844)) {
        return BKR_FALSE;
    }
    return BKR_TRUE;
}

bkr_str _v2851(bkr_str _v2852, bkr_str _v2844) {
    if ((bkr_len((bkr_str)(intptr_t)(_v2852)) <= 0)) {
        return _v2844;
    }
    return bkr_str_concat(bkr_str_concat(_v2852, "/"), _v2844);
}

bkr_str _v2853(bkr_str _v2854) {
    bkr_i64 _v2855 = (-1);
    bkr_i64 _v1172 = 0;
    while ((_v1172 < bkr_len((bkr_str)(intptr_t)(_v2854)))) {
        if (((char_code_at(_v2854, _v1172) == 47) || (char_code_at(_v2854, _v1172) == 92))) {
            _v2855 = _v1172;
        }
        _v1172 = (_v1172 + 1);
    }
    if ((_v2855 < 0)) {
        return "";
    }
    return substring(_v2854, 0, _v2855);
}

bkr_bool _v2856(bkr_i64 _v2729, bkr_str _v2844) {
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v2729))) {
        if (bkr_str_eq(vec_get(_v2729, _v1172), _v2844)) {
            return BKR_TRUE;
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_FALSE;
}

bkr_str _v2857(bkr_str _v2858, bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852) {
    if (_v2839(_v1598)) {
        bkr_str _v2844 = _v2842(_v1598);
        if ((!_v2850(_v2844))) {
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2858, "// Invalid import path: "), _v2844), from_char_code(10));
        }
        bkr_str _v2854 = _v2851(_v2852, _v2844);
        if ((!file_exists(_v2854))) {
            return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2858, "// Missing import: "), _v2854), from_char_code(10));
        }
        if (_v2856(_v2729, _v2854)) {
            return _v2858;
        }
        vec_push(_v2729, ((bkr_i64)(intptr_t)_v2854));
        bkr_str _v2860 = read_file(_v2854);
        bkr_str _v2862 = _v2863(_v2860, _v2729, _v2853(_v2854));
        bkr_str _v1196 = bkr_str_concat(_v2858, _v2862);
        if (((bkr_len((bkr_str)(intptr_t)(_v1196)) > 0) && (char_code_at(_v1196, (bkr_len((bkr_str)(intptr_t)(_v1196)) - 1)) != 10))) {
            _v1196 = bkr_str_concat(_v1196, from_char_code(10));
        }
        return _v1196;
    }
    return bkr_str_concat(bkr_str_concat(_v2858, _v1598), from_char_code(10));
}

bkr_str _v2863(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852) {
    bkr_str _v2858 = "";
    bkr_i64 _v339 = 0;
    bkr_i64 _v1213 = 0;
    bkr_i64 _v2864 = bkr_len((bkr_str)(intptr_t)(_v1212));
    while ((_v1213 < _v2864)) {
        if ((char_code_at(_v1212, _v1213) == 10)) {
            _v2858 = _v2857(_v2858, substring(_v1212, _v339, _v1213), _v2729, _v2852);
            _v1213 = (_v1213 + 1);
            _v339 = _v1213;
        } else {
            _v1213 = (_v1213 + 1);
        }
    }
    if ((_v339 < _v2864)) {
        _v2858 = _v2857(_v2858, substring(_v1212, _v339, _v2864), _v2729, _v2852);
    }
    return _v2858;
}

bkr_str _v2865(bkr_str _v1212) {
    return _v2866(_v1212, "");
}

bkr_str _v2866(bkr_str _v1212, bkr_str _v2852) {
    bkr_i64 _v2729 = vec_new();
    return _v2863(_v1212, _v2729, _v2852);
}

bkr_str _v2867(bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852) {
    if (_v2839(_v1598)) {
        bkr_str _v2844 = _v2842(_v1598);
        if ((!_v2850(_v2844))) {
            return "";
        }
        bkr_str _v2854 = _v2851(_v2852, _v2844);
        if ((!file_exists(_v2854))) {
            return _v2854;
        }
        if (_v2856(_v2729, _v2854)) {
            return "";
        }
        vec_push(_v2729, ((bkr_i64)(intptr_t)_v2854));
        return _v2868(read_file(_v2854), _v2729, _v2853(_v2854));
    }
    return "";
}

bkr_str _v2868(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852) {
    bkr_i64 _v339 = 0;
    bkr_i64 _v1213 = 0;
    bkr_i64 _v2864 = bkr_len((bkr_str)(intptr_t)(_v1212));
    while ((_v1213 < _v2864)) {
        if ((char_code_at(_v1212, _v1213) == 10)) {
            bkr_str _v2329 = _v2867(substring(_v1212, _v339, _v1213), _v2729, _v2852);
            if ((bkr_len((bkr_str)(intptr_t)(_v2329)) > 0)) {
                return _v2329;
            }
            _v1213 = (_v1213 + 1);
            _v339 = _v1213;
        } else {
            _v1213 = (_v1213 + 1);
        }
    }
    if ((_v339 < _v2864)) {
        return _v2867(substring(_v1212, _v339, _v2864), _v2729, _v2852);
    }
    return "";
}

bkr_str _v2869(bkr_str _v1212) {
    return _v2870(_v1212, "");
}

bkr_str _v2870(bkr_str _v1212, bkr_str _v2852) {
    bkr_i64 _v2729 = vec_new();
    return _v2868(_v1212, _v2729, _v2852);
}

bkr_str _v2871(bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852) {
    if (_v2839(_v1598)) {
        bkr_str _v2844 = _v2842(_v1598);
        if ((!_v2850(_v2844))) {
            return _v2844;
        }
        bkr_str _v2854 = _v2851(_v2852, _v2844);
        if ((!file_exists(_v2854))) {
            return "";
        }
        if (_v2856(_v2729, _v2854)) {
            return "";
        }
        vec_push(_v2729, ((bkr_i64)(intptr_t)_v2854));
        return _v2872(read_file(_v2854), _v2729, _v2853(_v2854));
    }
    return "";
}

bkr_str _v2872(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852) {
    bkr_i64 _v339 = 0;
    bkr_i64 _v1213 = 0;
    bkr_i64 _v2864 = bkr_len((bkr_str)(intptr_t)(_v1212));
    while ((_v1213 < _v2864)) {
        if ((char_code_at(_v1212, _v1213) == 10)) {
            bkr_str _v2873 = _v2871(substring(_v1212, _v339, _v1213), _v2729, _v2852);
            if ((bkr_len((bkr_str)(intptr_t)(_v2873)) > 0)) {
                return _v2873;
            }
            _v1213 = (_v1213 + 1);
            _v339 = _v1213;
        } else {
            _v1213 = (_v1213 + 1);
        }
    }
    if ((_v339 < _v2864)) {
        return _v2871(substring(_v1212, _v339, _v2864), _v2729, _v2852);
    }
    return "";
}

bkr_str _v2874(bkr_str _v1212) {
    return _v2875(_v1212, "");
}

bkr_str _v2875(bkr_str _v1212, bkr_str _v2852) {
    bkr_i64 _v2729 = vec_new();
    return _v2872(_v1212, _v2729, _v2852);
}

bkr_i64 _v2876(bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852) {
    if (_v2839(_v1598)) {
        bkr_str _v2844 = _v2842(_v1598);
        if ((!_v2850(_v2844))) {
            return 0;
        }
        bkr_str _v2854 = _v2851(_v2852, _v2844);
        if ((!file_exists(_v2854))) {
            return 0;
        }
        if (_v2856(_v2729, _v2854)) {
            return 0;
        }
        vec_push(_v2729, ((bkr_i64)(intptr_t)_v2854));
        return (1 + _v2877(read_file(_v2854), _v2729, _v2853(_v2854)));
    }
    return 0;
}

bkr_i64 _v2877(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852) {
    bkr_i64 _v399 = 0;
    bkr_i64 _v339 = 0;
    bkr_i64 _v1213 = 0;
    bkr_i64 _v2864 = bkr_len((bkr_str)(intptr_t)(_v1212));
    while ((_v1213 < _v2864)) {
        if ((char_code_at(_v1212, _v1213) == 10)) {
            _v399 = (_v399 + _v2876(substring(_v1212, _v339, _v1213), _v2729, _v2852));
            _v1213 = (_v1213 + 1);
            _v339 = _v1213;
        } else {
            _v1213 = (_v1213 + 1);
        }
    }
    if ((_v339 < _v2864)) {
        _v399 = (_v399 + _v2876(substring(_v1212, _v339, _v2864), _v2729, _v2852));
    }
    return _v399;
}

bkr_i64 _v2878(bkr_str _v1212) {
    return _v2879(_v1212, "");
}

bkr_i64 _v2879(bkr_str _v1212, bkr_str _v2852) {
    bkr_i64 _v2729 = vec_new();
    return _v2877(_v1212, _v2729, _v2852);
}

bkr_str _v2880(bkr_str _v1196, bkr_str _v558) {
    if ((bkr_len((bkr_str)(intptr_t)(_v1196)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1196, ","), _v558);
    }
    return bkr_str_concat(_v1196, _v558);
}

bkr_str _v2881(bkr_str _v1196, bkr_str _v423) {
    if ((bkr_len((bkr_str)(intptr_t)(_v423)) <= 2)) {
        return _v1196;
    }
    bkr_str _v2013 = substring(_v423, 1, (bkr_len((bkr_str)(intptr_t)(_v423)) - 1));
    if ((bkr_len((bkr_str)(intptr_t)(_v1196)) > 1)) {
        return bkr_str_concat(bkr_str_concat(_v1196, ","), _v2013);
    }
    return bkr_str_concat(_v1196, _v2013);
}

bkr_str _v2882(bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852) {
    bkr_str _v1196 = "[";
    if (_v2839(_v1598)) {
        bkr_str _v2844 = _v2842(_v1598);
        if ((!_v2850(_v2844))) {
            return bkr_str_concat(_v1196, "]");
        }
        bkr_str _v2854 = _v2851(_v2852, _v2844);
        if ((!file_exists(_v2854))) {
            return bkr_str_concat(_v1196, "]");
        }
        if (_v2856(_v2729, _v2854)) {
            return bkr_str_concat(_v1196, "]");
        }
        vec_push(_v2729, ((bkr_i64)(intptr_t)_v2854));
        _v1196 = _v2880(_v1196, _v1948(_v2854));
        _v1196 = _v2881(_v1196, _v2883(read_file(_v2854), _v2729, _v2853(_v2854)));
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2883(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852) {
    bkr_str _v1196 = "[";
    bkr_i64 _v339 = 0;
    bkr_i64 _v1213 = 0;
    bkr_i64 _v2864 = bkr_len((bkr_str)(intptr_t)(_v1212));
    while ((_v1213 < _v2864)) {
        if ((char_code_at(_v1212, _v1213) == 10)) {
            _v1196 = _v2881(_v1196, _v2882(substring(_v1212, _v339, _v1213), _v2729, _v2852));
            _v1213 = (_v1213 + 1);
            _v339 = _v1213;
        } else {
            _v1213 = (_v1213 + 1);
        }
    }
    if ((_v339 < _v2864)) {
        _v1196 = _v2881(_v1196, _v2882(substring(_v1212, _v339, _v2864), _v2729, _v2852));
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2884(bkr_str _v1212) {
    return _v2885(_v1212, "");
}

bkr_str _v2885(bkr_str _v1212, bkr_str _v2852) {
    bkr_i64 _v2729 = vec_new();
    return _v2883(_v1212, _v2729, _v2852);
}

bkr_str _v2886(bkr_str _v2887, bkr_str _v2888, bkr_str _v2889, bkr_str _v2532) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("from_base", _v2887)), _v1955), _v1907("requested", _v2888)), _v1955), _v1907("resolved", _v2889)), _v1955), _v1907("status", _v2532)), "}");
}

bkr_str _v2890(bkr_str _v1598, bkr_i64 _v2729, bkr_str _v2852) {
    bkr_str _v1196 = "[";
    if (_v2839(_v1598)) {
        bkr_str _v2844 = _v2842(_v1598);
        if ((!_v2850(_v2844))) {
            return bkr_str_concat(_v2880(_v1196, _v2886(_v2852, _v2844, "", "invalid")), "]");
        }
        bkr_str _v2854 = _v2851(_v2852, _v2844);
        if ((!file_exists(_v2854))) {
            return bkr_str_concat(_v2880(_v1196, _v2886(_v2852, _v2844, _v2854, "missing")), "]");
        }
        if (_v2856(_v2729, _v2854)) {
            return bkr_str_concat(_v2880(_v1196, _v2886(_v2852, _v2844, _v2854, "duplicate")), "]");
        }
        vec_push(_v2729, ((bkr_i64)(intptr_t)_v2854));
        _v1196 = _v2880(_v1196, _v2886(_v2852, _v2844, _v2854, "ok"));
        _v1196 = _v2881(_v1196, _v2891(read_file(_v2854), _v2729, _v2853(_v2854)));
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2891(bkr_str _v1212, bkr_i64 _v2729, bkr_str _v2852) {
    bkr_str _v1196 = "[";
    bkr_i64 _v339 = 0;
    bkr_i64 _v1213 = 0;
    bkr_i64 _v2864 = bkr_len((bkr_str)(intptr_t)(_v1212));
    while ((_v1213 < _v2864)) {
        if ((char_code_at(_v1212, _v1213) == 10)) {
            _v1196 = _v2881(_v1196, _v2890(substring(_v1212, _v339, _v1213), _v2729, _v2852));
            _v1213 = (_v1213 + 1);
            _v339 = _v1213;
        } else {
            _v1213 = (_v1213 + 1);
        }
    }
    if ((_v339 < _v2864)) {
        _v1196 = _v2881(_v1196, _v2890(substring(_v1212, _v339, _v2864), _v2729, _v2852));
    }
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2892(bkr_str _v1212, bkr_str _v2852) {
    bkr_i64 _v2729 = vec_new();
    return _v2891(_v1212, _v2729, _v2852);
}

bkr_i64 _v2893(bkr_str _v2894, bkr_str _v2532) {
    bkr_str _v1811 = from_char_code(34);
    bkr_str _v2895 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v1811, "status"), _v1811), ":"), _v1948(_v2532));
    bkr_i64 _v399 = 0;
    bkr_i64 _v1172 = 0;
    while (((_v1172 + bkr_len((bkr_str)(intptr_t)(_v2895))) <= bkr_len((bkr_str)(intptr_t)(_v2894)))) {
        if (bkr_str_eq(substring(_v2894, _v1172, (_v1172 + bkr_len((bkr_str)(intptr_t)(_v2895)))), _v2895)) {
            _v399 = (_v399 + 1);
            _v1172 = (_v1172 + bkr_len((bkr_str)(intptr_t)(_v2895)));
        } else {
            _v1172 = (_v1172 + 1);
        }
    }
    return _v399;
}

bkr_i64 _v2896(bkr_str _v1212, bkr_str _v2852, bkr_str _v2532) {
    return _v2893(_v2892(_v1212, _v2852), _v2532);
}

bkr_i64 _v2897(bkr_str _v1212, bkr_str _v2852) {
    return (((_v2896(_v1212, _v2852, "ok") + _v2896(_v1212, _v2852, "missing")) + _v2896(_v1212, _v2852, "invalid")) + _v2896(_v1212, _v2852, "duplicate"));
}

bkr_i64 _v2898(bkr_str _v1212, bkr_i64 _v1289) {
    bkr_i64 _v1598 = 1;
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2864 = bkr_len((bkr_str)(intptr_t)(_v1212));
    while (((_v1172 < _v1289) && (_v1172 < _v2864))) {
        if ((char_code_at(_v1212, _v1172) == 10)) {
            _v1598 = (_v1598 + 1);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v1598;
}

bkr_i64 _v2899(bkr_str _v1212, bkr_i64 _v1289) {
    bkr_i64 _v2900 = 1;
    bkr_i64 _v1172 = 0;
    bkr_i64 _v2864 = bkr_len((bkr_str)(intptr_t)(_v1212));
    while (((_v1172 < _v1289) && (_v1172 < _v2864))) {
        if ((char_code_at(_v1212, _v1172) == 10)) {
            _v2900 = 1;
        } else {
            _v2900 = (_v2900 + 1);
        }
        _v1172 = (_v1172 + 1);
    }
    return _v2900;
}

bkr_str _v2901(bkr_str _v1212, bkr_i64 _v1289) {
    bkr_i64 _v2864 = bkr_len((bkr_str)(intptr_t)(_v1212));
    if ((_v2864 <= 0)) {
        return "";
    }
    bkr_i64 _v2902 = _v1289;
    if ((_v2902 < 0)) {
        _v2902 = 0;
    }
    if ((_v2902 >= _v2864)) {
        _v2902 = (_v2864 - 1);
    }
    bkr_i64 _v339 = _v2902;
    while (((_v339 > 0) && (char_code_at(_v1212, (_v339 - 1)) != 10))) {
        _v339 = (_v339 - 1);
    }
    bkr_i64 _v340 = _v2902;
    while (((_v340 < _v2864) && (char_code_at(_v1212, _v340) != 10))) {
        _v340 = (_v340 + 1);
    }
    return substring(_v1212, _v339, _v340);
}

bkr_str _v2903(bkr_str _v330, bkr_str _v1244, bkr_str _v2501, bkr_i64 _v1950, bkr_i64 _v1951, bkr_i64 _v2904, bkr_i64 _v2905, bkr_str _v2906, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117) {
    return _v2907(_v330, _v1244, _v2501, _v1950, _v1951, _v2904, _v2905, _v2906, _v1279, _v1282, _v2117, BKR_FALSE, _v1956());
}

bkr_str _v2907(bkr_str _v330, bkr_str _v1244, bkr_str _v2501, bkr_i64 _v1950, bkr_i64 _v1951, bkr_i64 _v2904, bkr_i64 _v2905, bkr_str _v2906, bkr_str _v1279, bkr_str _v1282, bkr_str _v2117, bkr_bool _v2908, bkr_str _v2909) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.self_host.diagnostic.v1")), _v1955), _v1907("phase", _v330)), _v1955), _v1907("category", _v330)), _v1955), _v1907("error_code", _v1244)), _v1955), _v1907("rule_id", _v1244)), _v1955), _v1907("severity", "error")), _v1955), _v1907("message", _v2501)), _v1955), _v1908("source_start", _v1950)), _v1955), _v1908("source_end", _v1951)), _v1955), _v1908("source_line", _v2904)), _v1955), _v1908("source_column", _v2905)), _v1955), _v1907("source_excerpt", _v2906)), _v1955), _v1907("expected", _v1279)), _v1955), _v1907("actual", _v1282)), _v1955), _v1907("suggested_action", _v2117)), _v1955), _v1907("fix_applicability", "manual_review")), _v1955), _v1907("fix_confidence", "medium")), _v1955), _v1909("safe_edit_available", _v2908)), _v1955), _v1910("suggested_edits", _v2909)), _v1955), _v1907("repair_hint", _v2117)), "}");
}

bkr_str _v2910(bkr_i64 _v2911) {
    if ((_v2911 == _v192)) {
        return ";";
    }
    if ((_v2911 == _v186)) {
        return ")";
    }
    if ((_v2911 == _v188)) {
        return "}";
    }
    if ((_v2911 == _v190)) {
        return "]";
    }
    if ((_v2911 == _v191)) {
        return ",";
    }
    if ((_v2911 == _v193)) {
        return ":";
    }
    return "";
}

bkr_str _v2912(bkr_str _v1244, bkr_str _v2913, bkr_str _v330, bkr_str _v2914) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("code", _v1244)), _v1955), _v1907("rule_id", _v1244)), _v1955), _v1907("phase", _v2913)), _v1955), _v1907("category", _v330)), _v1955), _v1907("description", _v2914)), "}");
}

bkr_str _v2915(void) {
    bkr_str _v1196 = "[";
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_PARSE", "parse", "syntax", "Parse error with expected and actual token details."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_IMPORT_PATH", "import", "module", "Invalid normalized relative import path."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_IMPORT", "import", "module", "Missing imported module."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_IMPORT_CYCLE", "import", "module", "Cyclic dependency detected in import graph."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_VISIBILITY", "resolver", "visibility", "Attempt to access private symbol across kernel or module boundaries."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_DUPLICATE_SYMBOL", "resolver", "name_resolution", "Duplicate declaration in a scope."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_UNRESOLVED_SYMBOL", "resolver", "name_resolution", "Unresolved identifier, function, type, struct literal, or field reference."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_TYPE_MISMATCH", "typecheck", "type_system", "Expected/found type mismatch."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_ARITY_MISMATCH", "typecheck", "type_system", "Function call argument count mismatch."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_ASSIGNMENT_TARGET", "typecheck", "type_system", "Invalid non-assignable assignment target."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_CONTROL_FLOW", "typecheck", "control_flow", "Invalid break or continue outside a loop."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_RETURN_PATH", "typecheck", "control_flow", "Non-void function can fall through without returning a value."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_UNREACHABLE_CODE", "typecheck", "control_flow", "Statement cannot execute because a previous statement terminates control flow."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_MATCH_PATTERN", "typecheck", "pattern_matching", "Duplicate or unreachable match pattern."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_EXHAUSTIVENESS", "typecheck", "pattern_matching", "Non-exhaustive match for a known finite scrutinee."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_STRUCT_LITERAL", "typecheck", "data_model", "Invalid struct literal shape such as duplicate or missing fields."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_CONST_ASSIGNMENT", "typecheck", "control_flow", "Assignment attempts to modify a top-level constant."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_AMBIGUOUS_TYPE", "typecheck", "type_system", "Expression requires a type annotation or contextual type."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_VOID_VALUE", "typecheck", "type_system", "Void expression is used where a value is required."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_ENTRY_POINT", "typecheck", "program_structure", "Kernel entry function is missing."));
    _v1196 = _v2880(_v1196, _v2912("BKR_SELF_CALL_TARGET", "typecheck", "type_system", "Known non-function symbol is used as a call target."));
    return bkr_str_concat(_v1196, "]");
}

bkr_str _v2916(void) {
    bkr_str _v1955 = ",";
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.self_host.capability.v1")), _v1955), _v1907("compiler", "bkrc-self-host-bootstrap")), _v1955), _v1907("agent_contract_version", "bunker.agent.diagnostics.v1")), _v1955), _v1907("self_hosting_stage", "bootstrap-self-hosted-reports")), _v1955), _v1909("ai_agent_native_diagnostics", BKR_TRUE)), _v1955), _v1909("production_language_ready", BKR_FALSE)), _v1955), _v1909("requires_ci_validation", BKR_TRUE)), _v1955), _v1909("source_byte_spans", BKR_TRUE)), _v1955), _v1909("source_excerpts", BKR_TRUE)), _v1955), _v1909("structured_repair_metadata", BKR_TRUE)), _v1955), _v1909("structured_parse_diagnostics", BKR_TRUE)), _v1955), _v1909("diagnostic_code_registry", BKR_TRUE)), _v1955), _v1909("diagnostic_phase_field", BKR_TRUE)), _v1955), _v1909("diagnostic_rule_ids", BKR_TRUE)), _v1955), _v1909("diagnostic_severity", BKR_TRUE)), _v1955), _v1909("diagnostic_severity_counts", BKR_TRUE)), _v1955), _v1909("suggested_edit_envelope", BKR_TRUE)), _v1955), _v1909("import_expansion", BKR_TRUE)), _v1955), _v1909("import_graph_report", BKR_TRUE)), _v1955), _v1909("import_duplicate_or_cycle_summary", BKR_TRUE)), _v1955), _v1909("stage1_stage2_ci_gate", BKR_TRUE)), _v1955), _v1909("type_graph_report", BKR_TRUE)), _v1955), _v1909("symbol_table_report", BKR_TRUE)), _v1955), _v1909("name_resolver_report", BKR_TRUE)), _v1955), _v1909("typecheck_report", BKR_TRUE)), _v1955), _v1909("real_typechecker", BKR_TRUE)), _v1955), _v1909("full_subset_type_enforcement", BKR_TRUE)), _v1955), _v1909("modular_c_codegen", BKR_TRUE)), _v1955), _v1909("typed_c_emission", BKR_TRUE)), _v1955), _v1909("cgen_state_ref_routing", BKR_TRUE)), _v1955), _v1909("hygienic_temporaries", BKR_TRUE)), _v1955), _v1909("gnu_statement_expressions_locked", BKR_TRUE)), _v1955), _v1909("c99_standard_portability", BKR_TRUE)), _v1955), _v1909("multi_target_backend_strategy", BKR_TRUE)), _v1955), _v1909("deterministic_artifact_layout", BKR_TRUE)), _v1955), _v1907("supported_backends", "c, cranelift, llvm")), _v1955), _v1909("constant_folding", BKR_TRUE)), _v1955), _v1909("dead_code_elimination", BKR_TRUE)), _v1955), _v1909("incremental_compilation_cache", BKR_TRUE)), _v1955), _v1909("debug_info_source_mapping", BKR_TRUE)), _v1955), _v1909("source_line_directives", BKR_TRUE)), _v1955), _v1909("closures", BKR_TRUE)), _v1955), _v1909("lambdas", BKR_TRUE)), _v1955), _v1909("closure_captures", BKR_TRUE)), _v1955), _v1909("code_formatter", BKR_TRUE)), _v1955), _v1909("static_linter", BKR_TRUE)), _v1955), _v1909("test_runner", BKR_TRUE)), _v1955), _v1909("doc_generator", BKR_TRUE)), _v1955), _v1909("package_manager", BKR_TRUE)), _v1955), _v1909("build_cache", BKR_TRUE)), _v1955), _v1909("language_server", BKR_TRUE)), _v1955), _v1909("watch_mode", BKR_TRUE)), _v1955), _v1909("debugger_hooks", BKR_TRUE)), _v1955), _v1909("profiler_hooks", BKR_TRUE)), _v1955), _v1909("coverage_tooling", BKR_TRUE)), _v1955), _v1909("benchmark_tooling", BKR_TRUE)), _v1955), _v1909("fuzzing_harness", BKR_TRUE)), _v1955), _v1909("differential_testing", BKR_TRUE)), _v1955), _v1909("property_testing", BKR_TRUE)), _v1955), _v1909("stress_testing", BKR_TRUE)), _v1955), _v1909("cross_platform_ci", BKR_TRUE)), _v1955), _v1909("versioning_rules", BKR_TRUE)), _v1955), _v1909("package_registry", BKR_TRUE)), _v1955), _v1909("stdlib_documentation", BKR_TRUE)), _v1955), _v1909("construct_examples", BKR_TRUE)), _v1955), _v1909("migration_guides", BKR_TRUE)), _v1955), _v1909("contribution_guide", BKR_TRUE)), _v1955), _v1909("spec_sync", BKR_TRUE)), _v1955), _v1909("roadmap_ci_gates", BKR_TRUE)), _v1955), _v1909("borrow_resource_checker", BKR_TRUE)), _v1955), _v1909("shell_actor_runtime", BKR_TRUE)), _v1955), _v1909("declarative_view_runtime", BKR_TRUE)), _v1955), _v1909("contract_verification", BKR_TRUE)), _v1955), _v1909("typed_ast", BKR_TRUE)), _v1955), _v1909("real_module_resolver", BKR_TRUE)), _v1955), _v1909("module_cycle_path_detection", BKR_TRUE)), _v1955), _v1909("visibility_boundary_enforcement", BKR_TRUE)), _v1955), _v1909("semantic_validation_passes", BKR_TRUE)), _v1955), _v1909("loop_control_validation", BKR_TRUE)), _v1955), _v1909("unreachable_code_detection", BKR_TRUE)), _v1955), _v1909("return_path_validation", BKR_TRUE)), _v1955), _v1909("real_generics", BKR_TRUE)), _v1955), _v1909("user_defined_adts", BKR_TRUE)), _v1955), _v1909("multi_error_recovery", BKR_TRUE)), _v1955), _v1909("multi_error_parse_recovery", BKR_TRUE)), _v1955), _v1909("parse_recovery_synchronization", BKR_TRUE)), _v1955), _v1910("diagnostic_codes", _v2915())), _v1955), _v1907("supported_constructs", "kernel, struct, fn, const, let, fixed arrays, field access, if, else, match, Option via Some and None, Result via result_* builtins, Vec<T> handles, HashMap<K,V> handles, for ranges, while, loop, break, continue, return, primitive types, calls, casts, ternary, bitwise operators, string literals, float literals, closures, lambdas")), _v1955), _v1907("known_limits", "byte spans only, no file span table; import graph with normalized relative path policy, exact cycle path detection, visibility boundary checking, pure typechecker, modular typed C codegen, debug source mapping, and semantic validation passes active")), _v1955), _v1907("agent_guidance", "Use BUNKER_CAPABILITY_JSON before generating Bunker code. Use BUNKER_DIAGNOSTIC_JSON, BUNKER_RESOLVER_JSON, and BUNKER_TYPECHECK_JSON for repair tasks. Treat production_language_ready=false as requiring CI validation before release.")), "}");
}

bkr_str _v2917(void) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_CAPABILITY_JSON: ", _v2916()), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v2918(bkr_str _v1212) {
    return _v2919(_v1212, "");
}

bkr_str _v2919(bkr_str _v1212, bkr_str _v2852) {
    bkr_str _v1955 = ",";
    bkr_str _v2920 = _v2875(_v1212, _v2852);
    bkr_str _v2921 = _v2870(_v1212, _v2852);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.self_host.import_graph.v1")), _v1955), _v1907("root_base_dir", _v2852)), _v1955), _v1907("path_policy", "normalized_relative_forward_slash")), _v1955), _v1909("base_directory_resolution", BKR_TRUE)), _v1955), _v1909("recursive_expansion", BKR_TRUE)), _v1955), _v1909("duplicate_suppression", BKR_TRUE)), _v1955), _v1909("cycle_safe_expansion", BKR_TRUE)), _v1955), _v1908("unique_import_count", _v2879(_v1212, _v2852))), _v1955), _v1908("edge_count", _v2897(_v1212, _v2852))), _v1955), _v1908("ok_edge_count", _v2896(_v1212, _v2852, "ok"))), _v1955), _v1908("missing_edge_count", _v2896(_v1212, _v2852, "missing"))), _v1955), _v1908("invalid_edge_count", _v2896(_v1212, _v2852, "invalid"))), _v1955), _v1908("duplicate_edge_count", _v2896(_v1212, _v2852, "duplicate"))), _v1955), _v1908("duplicate_or_cycle_edge_count", _v2896(_v1212, _v2852, "duplicate"))), _v1955), _v1910("imports", _v2885(_v1212, _v2852))), _v1955), _v1910("edges", _v2892(_v1212, _v2852))), _v1955), _v1909("has_duplicate_or_cycle_import", (_v2896(_v1212, _v2852, "duplicate") > 0))), _v1955), _v1909("has_invalid_import", (bkr_len((bkr_str)(intptr_t)(_v2920)) > 0))), _v1955), _v1907("invalid_import", _v2920)), _v1955), _v1909("has_missing_import", (bkr_len((bkr_str)(intptr_t)(_v2921)) > 0))), _v1955), _v1907("missing_import", _v2921)), "}");
}

bkr_str _v2922(bkr_str _v1212) {
    return _v2923(_v1212, "");
}

bkr_str _v2923(bkr_str _v1212, bkr_str _v2852) {
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* BUNKER_IMPORT_GRAPH_JSON: ", _v2919(_v1212, _v2852)), from_char_code(10)), "*/"), from_char_code(10));
}

bkr_str _v2924(bkr_str _v2920) {
    bkr_str _v2117 = "Use a normalized relative import path such as modules/example.bkr. Do not use empty paths, absolute paths, drive prefixes, backslashes, parent traversal, leading ./, trailing /, or // segments.";
    bkr_str _v2501 = bkr_str_concat("Import error: invalid import path ", _v2920);
    bkr_str _v2925 = _v2903("import", "BKR_SELF_IMPORT_PATH", _v2501, 0, 0, 1, 1, "", "normalized relative forward-slash import path", _v2920, _v2117);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* ", _v2501), ". AI repair hint: "), _v2117), from_char_code(10)), "BUNKER_DIAGNOSTIC_JSON: "), _v2925), from_char_code(10)), "*/");
}

bkr_str _v2926(bkr_str _v2921) {
    bkr_str _v2117 = "Copy the imported Bunker module next to self_host_input.bkr or pre-expand imports before running bkrc.";
    bkr_str _v2501 = bkr_str_concat("Import error: missing module ", _v2921);
    bkr_str _v2925 = _v2903("import", "BKR_SELF_IMPORT", _v2501, 0, 0, 1, 1, "", "existing imported module", _v2921, _v2117);
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("/* ", _v2501), ". AI repair hint: "), _v2117), from_char_code(10)), "BUNKER_DIAGNOSTIC_JSON: "), _v2925), from_char_code(10)), "*/");
}

bkr_str _v2927(bkr_str _v1212, _v1249 _v1261) {
    bkr_i64 _v2928 = _v1317(_v1261);
    bkr_str _v2929 = _v1321(_v1314(_v1261));
    bkr_str _v2930 = _v1321(_v1316(_v1261));
    _v338 _v2931 = _v1353(_v1261);
    bkr_i64 _v1950 = _v2931._v339;
    bkr_i64 _v2932 = _v1950;
    bkr_i64 _v2933 = _v2931._v340;
    bkr_i64 _v2934 = _v2898(_v1212, _v2932);
    bkr_i64 _v2935 = _v2899(_v1212, _v2932);
    bkr_str _v2906 = _v2901(_v1212, _v1950);
    bkr_str _v2936 = _v2906;
    bkr_str _v2117 = "Inspect the construct before this token. Supported bootstrap syntax includes kernel, struct, fn, const, let, fixed arrays, field access, if, else, match expressions, Option<T> via Some/None, Result<T,E> via result_* builtins, Vec<T> and HashMap<i32,V> runtime handles, for-in ranges, while, loop, break, continue, return, primitive types, calls, casts, ternary expressions, bitwise operators, and basic expressions.";
    bkr_str _v2937 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Parse error at token ", int_to_string(_v1299(_v1261))), ": expected "), _v2929), ", got "), _v2930);
    bkr_str _v2938 = _v2910(_v1314(_v1261));
    bkr_str _v2939 = _v1956();
    bkr_bool _v2940 = BKR_FALSE;
    if ((bkr_len((bkr_str)(intptr_t)(_v2938)) > 0)) {
        _v2939 = _v1957(_v1949("insert_text", _v2932, _v2932, _v2938, "manual_review", "medium"));
        _v2940 = BKR_TRUE;
    }
    bkr_str _v2941 = "[";
    bkr_i64 _v1172 = 0;
    bkr_str _v2942 = "";
    while ((_v1172 < _v2928)) {
        bkr_i64 _v2943 = _v1319(_v1261, _v1172);
        bkr_i64 _v2944 = _v1320(_v1261, _v1172);
        bkr_i64 _v1213 = _v1318(_v1261, _v1172);
        bkr_str _v2945 = _v1321(_v2943);
        bkr_str _v2946 = _v1321(_v2944);
        _v338 _v457 = _v1354(_v1261, _v1172);
        bkr_i64 _v2947 = _v457._v339;
        bkr_i64 _v2948 = _v457._v340;
        bkr_i64 _v2949 = _v2898(_v1212, _v2947);
        bkr_i64 _v2950 = _v2899(_v1212, _v2947);
        bkr_str _v2951 = _v2901(_v1212, _v2947);
        bkr_str _v2952 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Parse error at token ", int_to_string(_v1213)), ": expected "), _v2945), ", got "), _v2946);
        bkr_str _v2953 = _v2910(_v2943);
        bkr_str _v2954 = _v1956();
        bkr_bool _v2955 = BKR_FALSE;
        if ((bkr_len((bkr_str)(intptr_t)(_v2953)) > 0)) {
            _v2954 = _v1957(_v1949("insert_text", _v2947, _v2947, _v2953, "manual_review", "medium"));
            _v2955 = BKR_TRUE;
        }
        bkr_str _v2956 = _v2907("parse", "BKR_SELF_PARSE", _v2952, _v2947, _v2948, _v2949, _v2950, _v2951, _v2945, _v2946, _v2117, _v2955, _v2954);
        _v2941 = _v2880(_v2941, _v2956);
        _v2942 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2942, "/* "), _v2952), ". AI repair hint: "), _v2117), " */"), from_char_code(10));
        _v1172 = (_v1172 + 1);
    }
    _v2941 = bkr_str_concat(_v2941, "]");
    bkr_str _v1955 = ",";
    bkr_str _v2925 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("{", _v1907("schema_version", "bunker.self_host.diagnostic.v1")), _v1955), _v1907("phase", "parse")), _v1955), _v1907("category", "syntax")), _v1955), _v1907("error_code", "BKR_SELF_PARSE")), _v1955), _v1907("rule_id", "BKR_SELF_PARSE")), _v1955), _v1907("severity", "error")), _v1955), _v1908("error_count", _v2928)), _v1955), _v1907("message", _v2937)), _v1955), _v1908("source_start", _v2932)), _v1955), _v1908("source_end", _v2933)), _v1955), _v1908("source_line", _v2934)), _v1955), _v1908("source_column", _v2935)), _v1955), _v1907("source_excerpt", _v2936)), _v1955), _v1907("expected", _v2929)), _v1955), _v1907("actual", _v2930)), _v1955), _v1907("suggested_action", _v2117)), _v1955), _v1907("fix_applicability", "manual_review")), _v1955), _v1907("fix_confidence", "medium")), _v1955), _v1909("safe_edit_available", _v2940)), _v1955), _v1910("suggested_edits", _v2939)), _v1955), _v1907("repair_hint", _v2117)), _v1955), _v1910("diagnostics", _v2941)), "}");
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2942, "/* BUNKER_DIAGNOSTIC_JSON: "), _v2925), from_char_code(10)), "*/");
}

bkr_bool _v2957(void) {
    return file_exists("self_host_trace.enabled");
}

bkr_i64 _v2958(bkr_str _v2913) {
    if (_v2957()) {
        bkr_str _v2959 = "self_host_trace.log";
        bkr_str _v2619 = "";
        if (file_exists(_v2959)) {
            _v2619 = read_file(_v2959);
        }
        write_file(_v2959, bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2619, "[self-host trace] "), _v2913), from_char_code(10)));
    }
    return 0;
}

bkr_str _v2961(bkr_str _v1212) {
    return _v2962(_v1212, "");
}

bkr_str _v2962(bkr_str _v1212, bkr_str _v2963) {
    _v2958("compile_to_c:begin");
    bkr_str _v2964 = _v2917();
    _v2958("compile_to_c:capability_report");
    bkr_str _v2965 = _v2923(_v1212, _v2963);
    _v2958("compile_to_c:import_graph_report");
    bkr_str _v2920 = _v2875(_v1212, _v2963);
    if ((bkr_len((bkr_str)(intptr_t)(_v2920)) > 0)) {
        _v2958("compile_to_c:invalid_import");
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2964, _v2965), _v2924(_v2920)), from_char_code(10));
    }
    bkr_str _v2921 = _v2870(_v1212, _v2963);
    if ((bkr_len((bkr_str)(intptr_t)(_v2921)) > 0)) {
        _v2958("compile_to_c:missing_import");
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2964, _v2965), _v2926(_v2921)), from_char_code(10));
    }
    bkr_str _v2966 = _v2866(_v1212, _v2963);
    _v2958("compile_to_c:imports_expanded");
    _v1190 _v1251 = _v1228(_v2966);
    _v2958("compile_to_c:tokenized");
    _v1249 _v1261 = _v1253(_v1251);
    _v2958("compile_to_c:parser_state");
    bkr_i64 _v2967 = _v1541(_v1261);
    _v2958("compile_to_c:parsed");
    if (_v1311(_v1261)) {
        _v2958("compile_to_c:parse_error");
        return bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2964, _v2965), _v2927(_v2966, _v1261)), from_char_code(10));
    }
    bkr_str _v2968 = _v2010(_v2966, _v2967);
    _v2958("compile_to_c:ast_report");
    bkr_str _v2969 = _v2115(_v2967);
    _v2958("compile_to_c:type_graph_report");
    bkr_str _v2970 = _v2055(_v2967);
    _v2958("compile_to_c:symbol_table_report");
    bkr_str _v2971 = _v2185(_v2967);
    _v2958("compile_to_c:resolver_report");
    _v2958("compile_to_c:typecheck_begin");
    bkr_str _v2972 = _v2407(_v2967);
    _v2958("compile_to_c:typecheck_report");
    bkr_str _v2973 = _v2499(_v2967, _v2966);
    _v2958("compile_to_c:semantic_report");
    bkr_str _v2974 = _v1897(_v2967);
    _v2958("compile_to_c:c_program");
    return bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2964, _v2965), _v2968), _v2969), _v2970), _v2971), _v2972), _v2973), _v2974);
}

bkr_bool _v2975(bkr_str _v2976) {
    bkr_str _v2977 = from_char_code(34);
    bkr_str _v2978 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2977, "has_diagnostics"), _v2977), ":true");
    if (contains(_v2976, _v2978)) {
        return BKR_TRUE;
    }
    if ((!contains(_v2976, "#include "))) {
        return BKR_TRUE;
    }
    return BKR_FALSE;
}

bkr_str _v2979(bkr_str _v1841, bkr_str _v2980) {
    if ((!bkr_env_has((bkr_str)(intptr_t)(_v1841)))) {
        return _v2980;
    }
    bkr_i64 _v387 = bkr_env_get((bkr_str)(intptr_t)(_v1841));
    return ({ bkr_i64 _match_val_0 = _v387; bkr_i64 _match_res_1 = 0; int _matched_2 = 0; if (!_matched_2 && (((_match_val_0 & 1) != 0))) { bkr_i64 _v2213 = (_match_val_0 >> 1); _match_res_1 = _v2213; _matched_2 = 1; } if (!_matched_2 && ((_match_val_0 == 0))) { _match_res_1 = _v2980; _matched_2 = 1; } _match_res_1; });
}

bkr_str _v2984(bkr_str _v1305) {
    bkr_str _v2985 = from_char_code(39);
    return bkr_str_concat(bkr_str_concat(_v2985, bkr_str_replace((bkr_str)(intptr_t)(_v1305), (bkr_str)(intptr_t)(_v2985), (bkr_str)(intptr_t)(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2985, from_char_code(92)), _v2985), _v2985)))), _v2985);
}

bkr_str _v2987(void) {
    bkr_str _v2988 = _v2979("BKR_RUNTIME_DIR", "");
    if ((bkr_len((bkr_str)(intptr_t)(_v2988)) > 0)) {
        return _v2988;
    }
    bkr_str _v2989 = bkr_path_dir((bkr_str)(intptr_t)(bkr_arg_at(0)));
    if ((bkr_len((bkr_str)(intptr_t)(_v2989)) == 0)) {
        _v2989 = ".";
    }
    if (file_exists(bkr_str_concat(_v2989, "/bootstrap/runtime.h"))) {
        return bkr_str_concat(_v2989, "/bootstrap");
    }
    if (file_exists(bkr_str_concat(_v2989, "/runtime.h"))) {
        return _v2989;
    }
    return "bootstrap";
}

bkr_bool _v2992(bkr_str _v2976) {
    bkr_str _v2977 = from_char_code(34);
    bkr_str _v2993 = bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2977, "has_diagnostics"), _v2977), ":true");
    bkr_i64 _v1552 = bkr_str_split((bkr_str)(intptr_t)(_v2976), (bkr_str)(intptr_t)(from_char_code(10)));
    bkr_i64 _v1172 = 0;
    while ((_v1172 < vec_len(_v1552))) {
        bkr_str _v1598 = (bkr_str)(intptr_t)(vec_get(_v1552, _v1172));
        if (contains(_v1598, _v2993)) {
            bkr_println(_v1598);
        }
        _v1172 = (_v1172 + 1);
    }
    return BKR_TRUE;
}

bkr_bool _v2996(bkr_str _v2830) {
    if ((!file_exists(_v2830))) {
        return BKR_FALSE;
    }
    bkr_str _v1212 = read_file(_v2830);
    bkr_str _v2976 = _v2962(_v1212, _v2853(_v2830));
    return (!_v2975(_v2976));
}

bkr_str _v2997(void) {
    bkr_str _v2988 = _v2979("BKR_NATIVE_RUNTIME", "");
    if ((bkr_len((bkr_str)(intptr_t)(_v2988)) > 0)) {
        return _v2988;
    }
    bkr_str _v2989 = bkr_path_dir((bkr_str)(intptr_t)(bkr_arg_at(0)));
    if ((bkr_len((bkr_str)(intptr_t)(_v2989)) == 0)) {
        _v2989 = ".";
    }
    if (file_exists(bkr_str_concat(_v2989, "/self-host/native_runtime.bkr"))) {
        return bkr_str_concat(_v2989, "/self-host/native_runtime.bkr");
    }
    if (file_exists(bkr_str_concat(_v2989, "/native_runtime.bkr"))) {
        return bkr_str_concat(_v2989, "/native_runtime.bkr");
    }
    if (file_exists(bkr_str_concat(_v2989, "/../self-host/native_runtime.bkr"))) {
        return bkr_str_concat(_v2989, "/../self-host/native_runtime.bkr");
    }
    return "self-host/native_runtime.bkr";
}

bkr_bool _v2998(bkr_str _v2999, bkr_str _v3000) {
    bkr_str _v1212 = read_file(_v2999);
    bkr_str _v2852 = _v2853(_v2999);
    bkr_str _v2976 = _v2962(_v1212, _v2852);
    if (_v2975(_v2976)) {
        _v2992(_v2976);
        bkr_println(bkr_str_concat("Error: diagnostics found in ", _v2999));
        return BKR_FALSE;
    }
    bkr_str _v3001 = _v2997();
    if ((!file_exists(_v3001))) {
        bkr_println(bkr_str_concat(bkr_str_concat("Error: native runtime not found: ", _v3001), " (set BKR_NATIVE_RUNTIME)"));
        return BKR_FALSE;
    }
    bkr_str _v2966 = _v2866(_v1212, _v2852);
    bkr_i64 _v3002 = (bkr_len((bkr_str)(intptr_t)(_v2966)) - 1);
    while (((_v3002 >= 0) && (!bkr_str_eq(char_at(_v2966, _v3002), "}")))) {
        _v3002 = (_v3002 - 1);
    }
    if ((_v3002 < 0)) {
        bkr_println(bkr_str_concat("Error: no kernel body found in ", _v2999));
        return BKR_FALSE;
    }
    bkr_str _v3003 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(substring(_v2966, 0, _v3002), read_file(_v3001)), from_char_code(10)), "}"), from_char_code(10));
    _v1190 _v1251 = _v1228(_v3003);
    _v1249 _v1261 = _v1253(_v1251);
    bkr_i64 _v2967 = _v1541(_v1261);
    if (_v1311(_v1261)) {
        bkr_println(_v2927(_v3003, _v1261));
        bkr_println("Error: native runtime failed to parse");
        return BKR_FALSE;
    }
    _v2642 _v2424 = _v2817(_v477(_v2967));
    if ((vec_len(_v2424._v2643) > 0)) {
        bkr_i64 _v1172 = 0;
        while ((_v1172 < vec_len(_v2424._v2643))) {
            bkr_println(bkr_str_concat("Error: native backend: ", vec_get(_v2424._v2643, _v1172)));
            _v1172 = (_v1172 + 1);
        }
        return BKR_FALSE;
    }
    if ((!_v2829(_v3000, _v2827(_v2424._v1244)))) {
        bkr_println(bkr_str_concat("Error: cannot write ", _v3000));
        return BKR_FALSE;
    }
    return BKR_TRUE;
}

bkr_bool _v3004(void) {
    bkr_println("Usage: bkrc <command> [args]");
    bkr_println("  check <file.bkr>                 Parse, resolve and typecheck");
    bkr_println("  compile <file.bkr> [-o out.c]    Emit C for the program");
    bkr_println("  run <file.bkr> [--native]        Compile, build and execute; prints Result: <exit code>");
    bkr_println("  native <file.bkr> -o <exe>       Build a Linux x86-64 executable directly (no C compiler)");
    bkr_println("  parse <file.bkr> [--ast-json]    Print the AST report");
    bkr_println("  self-host-check [dir]            Check the self-host compiler sources");
    bkr_println("  capability                       Print the capability report");
    return BKR_TRUE;
}

bkr_i32 _v3005(void) {
    bkr_i64 _v2465 = bkr_args_count();
    if ((_v2465 <= 1)) {
        _v3004();
        return 1;
    }
    bkr_str _v3007 = bkr_arg_at(1);
    if ((bkr_str_eq(_v3007, "capability") || bkr_str_eq(_v3007, "--capability"))) {
        bkr_println(_v2916());
        return 0;
    }
    if (bkr_str_eq(_v3007, "self-host-check")) {
        bkr_str _v3008 = "self-host";
        bkr_i64 _v1172 = 2;
        while ((_v1172 < _v2465)) {
            bkr_str _v1817 = bkr_arg_at(_v1172);
            if (((!starts_with(_v1817, "-")) && (bkr_len((bkr_str)(intptr_t)(_v1817)) > 0))) {
                _v3008 = _v1817;
            }
            _v1172 = (_v1172 + 1);
        }
        if ((ends_with(_v3008, "/") || ends_with(_v3008, "\\"))) {
            _v3008 = substring(_v3008, 0, (bkr_len((bkr_str)(intptr_t)(_v3008)) - 1));
        }
        bkr_println(bkr_str_concat("Checking self-host sources in ", _v3008));
        bkr_i64 _v425 = bkr_str_split((bkr_str)(intptr_t)("bkrc.bkr,bkrc_simple.bkr,c_codegen.bkr,codegen.bkr,compiler.bkr,lexer.bkr,parser.bkr,typeck.bkr"), (bkr_str)(intptr_t)(","));
        bkr_i64 _v3009 = 0;
        bkr_i64 _v1645 = 0;
        while ((_v1645 < vec_len(_v425))) {
            bkr_str _v3010 = bkr_str_concat(bkr_str_concat(_v3008, "/"), vec_get(_v425, _v1645));
            if (_v2996(_v3010)) {
                bkr_println(bkr_str_concat("  PASS ", _v3010));
                _v3009 = (_v3009 + 1);
            } else {
                bkr_println(bkr_str_concat("  FAIL ", _v3010));
            }
            _v1645 = (_v1645 + 1);
        }
        bkr_println("");
        bkr_println(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat("Self-host readiness: ", int_to_string(_v3009)), "/"), int_to_string(vec_len(_v425))), " file(s) passing"));
        if ((_v3009 != vec_len(_v425))) {
            return 1;
        }
        return 0;
    }
    if (bkr_str_eq(_v3007, "check")) {
        bkr_str _v2999 = "";
        bkr_bool _v3011 = BKR_FALSE;
        bkr_bool _v3012 = BKR_FALSE;
        bkr_bool _v3013 = BKR_FALSE;
        bkr_bool _v3014 = BKR_FALSE;
        bkr_bool _v3015 = BKR_FALSE;
        bkr_bool _v3016 = BKR_FALSE;
        bkr_i64 _v1172 = 2;
        while ((_v1172 < _v2465)) {
            bkr_str _v1817 = bkr_arg_at(_v1172);
            if (bkr_str_eq(_v1817, "--capability-json")) {
                _v3011 = BKR_TRUE;
            } else {
                if (bkr_str_eq(_v1817, "--ast-json")) {
                    _v3012 = BKR_TRUE;
                } else {
                    if (bkr_str_eq(_v1817, "--type-graph")) {
                        _v3013 = BKR_TRUE;
                    } else {
                        if (bkr_str_eq(_v1817, "--symbol-table")) {
                            _v3014 = BKR_TRUE;
                        } else {
                            if (bkr_str_eq(_v1817, "--typecheck-json")) {
                                _v3015 = BKR_TRUE;
                            } else {
                                if (bkr_str_eq(_v1817, "--resolver-json")) {
                                    _v3016 = BKR_TRUE;
                                } else {
                                    if (((!starts_with(_v1817, "-")) && (bkr_len((bkr_str)(intptr_t)(_v2999)) == 0))) {
                                        _v2999 = bkr_arg_at(_v1172);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            _v1172 = (_v1172 + 1);
        }
        if (file_exists(bkr_str_concat(_v2999, "/bkrc.bkr"))) {
            _v2999 = bkr_str_concat(_v2999, "/bkrc.bkr");
        }
        if (((bkr_len((bkr_str)(intptr_t)(_v2999)) == 0) || (!file_exists(_v2999)))) {
            bkr_println(bkr_str_concat("Error: input file not found: ", _v2999));
            return 1;
        }
        bkr_str _v1212 = read_file(_v2999);
        bkr_str _v2976 = _v2962(_v1212, _v2853(_v2999));
        if ((((((_v3011 || _v3012) || _v3013) || _v3014) || _v3015) || _v3016)) {
            bkr_println(_v2976);
            return 0;
        }
        if (_v2975(_v2976)) {
            _v2992(_v2976);
            bkr_println(bkr_str_concat("Error: diagnostics found in ", _v2999));
            return 1;
        }
        bkr_println(bkr_str_concat("Checking ", _v2999));
        bkr_println("Success: No errors found.");
        return 0;
    }
    if (bkr_str_eq(_v3007, "run")) {
        bkr_str _v2999 = "";
        bkr_bool _v3017 = bkr_str_eq(_v2979("BKR_BACKEND", "c"), "native");
        bkr_i64 _v1172 = 2;
        while ((_v1172 < _v2465)) {
            bkr_str _v1817 = bkr_arg_at(_v1172);
            if (bkr_str_eq(_v1817, "--native")) {
                _v3017 = BKR_TRUE;
            } else {
                if (((!starts_with(_v1817, "-")) && (bkr_len((bkr_str)(intptr_t)(_v2999)) == 0))) {
                    _v2999 = bkr_arg_at(_v1172);
                }
            }
            _v1172 = (_v1172 + 1);
        }
        if (((bkr_len((bkr_str)(intptr_t)(_v2999)) == 0) || (!file_exists(_v2999)))) {
            bkr_println(bkr_str_concat("Error: input file not found: ", _v2999));
            return 1;
        }
        bkr_str _v3018 = bkr_str_concat(bkr_str_concat(_v2979("TMPDIR", "/tmp"), "/bkr-run-"), int_to_string(process_pid()));
        bkr_str _v3020 = bkr_str_concat(_v3018, ".out");
        bkr_str _v3021 = bkr_str_concat(_v3018, ".log");
        if (_v3017) {
            if ((!_v2998(_v2999, _v3020))) {
                return 1;
            }
        } else {
            bkr_str _v1212 = read_file(_v2999);
            bkr_str _v2976 = _v2962(_v1212, _v2853(_v2999));
            if (_v2975(_v2976)) {
                _v2992(_v2976);
                bkr_println(bkr_str_concat("Error: diagnostics found in ", _v2999));
                return 1;
            }
            bkr_str _v3022 = bkr_str_concat(_v3018, ".c");
            if ((!write_file(_v3022, _v2976))) {
                bkr_println(bkr_str_concat("Error: cannot write ", _v3022));
                return 1;
            }
            bkr_str _v2701 = _v2979("BKR_CC", _v2979("CC", "cc"));
            bkr_str _v3023 = bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2701, " -std=c11 -w -I "), _v2984(_v2987())), " "), _v2984(_v3022)), " -o "), _v2984(_v3020)), " -lm > "), _v2984(_v3021)), " 2>&1");
            bkr_i64 _v3024 = process_run_status(_v3023);
            bkr_i64 _v3026 = 1;
            if (bkr_result_is_ok(_v3024)) {
                _v3026 = bkr_result_unwrap(_v3024);
            }
            if ((_v3026 != 0)) {
                if (file_exists(_v3021)) {
                    bkr_print(read_file(_v3021));
                }
                bkr_println(bkr_str_concat("Error: C backend failed to build ", _v2999));
                file_remove(_v3022);
                file_remove(_v3021);
                return 1;
            }
            file_remove(_v3022);
        }
        bkr_i64 _v3030 = process_run_status(bkr_str_concat(bkr_str_concat(bkr_str_concat(_v2984(_v3020), " > "), _v2984(_v3021)), " 2>&1"));
        if ((!bkr_result_is_ok(_v3030))) {
            bkr_println(bkr_str_concat("Error: failed to execute ", _v3020));
            return 1;
        }
        bkr_i64 _v3031 = bkr_result_unwrap(_v3030);
        if (file_exists(_v3021)) {
            bkr_print(read_file(_v3021));
        }
        bkr_println(bkr_str_concat("Result: ", int_to_string(_v3031)));
        file_remove(_v3020);
        file_remove(_v3021);
        return ((bkr_i32)(_v3031));
    }
    if (bkr_str_eq(_v3007, "native")) {
        bkr_str _v2999 = "";
        bkr_str _v3000 = "";
        bkr_i64 _v1172 = 2;
        while ((_v1172 < _v2465)) {
            bkr_str _v1817 = bkr_arg_at(_v1172);
            if ((bkr_str_eq(_v1817, "-o") && ((_v1172 + 1) < _v2465))) {
                _v3000 = bkr_arg_at((_v1172 + 1));
                _v1172 = (_v1172 + 1);
            } else {
                if (((!starts_with(_v1817, "-")) && (bkr_len((bkr_str)(intptr_t)(_v2999)) == 0))) {
                    _v2999 = bkr_arg_at(_v1172);
                }
            }
            _v1172 = (_v1172 + 1);
        }
        if (((bkr_len((bkr_str)(intptr_t)(_v2999)) == 0) || (!file_exists(_v2999)))) {
            bkr_println(bkr_str_concat("Error: input file not found: ", _v2999));
            return 1;
        }
        if ((bkr_len((bkr_str)(intptr_t)(_v3000)) == 0)) {
            _v3000 = substring(_v2999, 0, (bkr_len((bkr_str)(intptr_t)(_v2999)) - 4));
        }
        if ((!_v2998(_v2999, _v3000))) {
            return 1;
        }
        return 0;
    }
    if (bkr_str_eq(_v3007, "parse")) {
        bkr_str _v2999 = "";
        bkr_bool _v3032 = BKR_FALSE;
        bkr_i64 _v1172 = 2;
        while ((_v1172 < _v2465)) {
            bkr_str _v1817 = bkr_arg_at(_v1172);
            if (bkr_str_eq(_v1817, "--ast-json")) {
                _v3032 = BKR_TRUE;
            } else {
                if (((!starts_with(_v1817, "-")) && (bkr_len((bkr_str)(intptr_t)(_v2999)) == 0))) {
                    _v2999 = bkr_arg_at(_v1172);
                }
            }
            _v1172 = (_v1172 + 1);
        }
        if (((bkr_len((bkr_str)(intptr_t)(_v2999)) == 0) || (!file_exists(_v2999)))) {
            bkr_println(bkr_str_concat("Error: input file not found: ", _v2999));
            return 1;
        }
        bkr_str _v1212 = read_file(_v2999);
        bkr_str _v2966 = _v2866(_v1212, _v2853(_v2999));
        _v1190 _v1251 = _v1228(_v2966);
        _v1249 _v1261 = _v1253(_v1251);
        bkr_i64 _v2967 = _v1541(_v1261);
        if (_v1311(_v1261)) {
            bkr_println(_v2927(_v2966, _v1261));
            return 1;
        }
        if (_v3032) {
            bkr_println(_v2004(_v2966, _v2967));
        } else {
            bkr_println(_v2010(_v2966, _v2967));
        }
        return 0;
    }
    if (((bkr_str_eq(_v3007, "self-host-compile") || bkr_str_eq(_v3007, "compile")) || bkr_str_eq(_v3007, "build"))) {
        bkr_str _v2999 = "";
        bkr_str _v3000 = "";
        bkr_i64 _v1172 = 2;
        while ((_v1172 < _v2465)) {
            bkr_str _v1817 = bkr_arg_at(_v1172);
            if ((bkr_str_eq(_v1817, "-o") && ((_v1172 + 1) < _v2465))) {
                _v3000 = bkr_arg_at((_v1172 + 1));
                _v1172 = (_v1172 + 1);
            } else {
                if (((!starts_with(_v1817, "-")) && (bkr_len((bkr_str)(intptr_t)(_v2999)) == 0))) {
                    _v2999 = bkr_arg_at(_v1172);
                }
            }
            _v1172 = (_v1172 + 1);
        }
        if (((bkr_len((bkr_str)(intptr_t)(_v2999)) == 0) || (!file_exists(_v2999)))) {
            bkr_println(bkr_str_concat("Error: input file not found: ", _v2999));
            return 1;
        }
        if ((bkr_len((bkr_str)(intptr_t)(_v3000)) == 0)) {
            _v3000 = bkr_str_concat(_v2999, ".c");
        }
        bkr_str _v1212 = read_file(_v2999);
        bkr_str _v2976 = _v2962(_v1212, _v2853(_v2999));
        bkr_bool _v3033 = write_file(_v3000, _v2976);
        if ((!_v3033)) {
            return 1;
        }
        return 0;
    }
    bkr_str _v2999 = bkr_arg_at(1);
    bkr_str _v3000 = bkr_str_concat(_v2999, ".c");
    bkr_i64 _v1172 = 2;
    while ((_v1172 < _v2465)) {
        bkr_str _v3034 = bkr_arg_at(_v1172);
        if ((bkr_str_eq(_v3034, "-o") && ((_v1172 + 1) < _v2465))) {
            _v3000 = bkr_arg_at((_v1172 + 1));
            _v1172 = (_v1172 + 1);
        }
        _v1172 = (_v1172 + 1);
    }
    if ((!file_exists(_v2999))) {
        bkr_println(bkr_str_concat("Error: input file not found: ", _v2999));
        return 1;
    }
    bkr_str _v1212 = read_file(_v2999);
    bkr_str _v2976 = _v2962(_v1212, _v2853(_v2999));
    bkr_bool _v3033 = write_file(_v3000, _v2976);
    if ((!_v3033)) {
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    bkr_init_args(argc, argv);
    return (int)_v3005();
}
