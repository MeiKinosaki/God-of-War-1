# God of War (PS2) → Xbox 360 RGH — plano técnico

> Estado inicial: planejamento técnico. Nenhuma compilação, execução no Xbox 360 ou compatibilidade foi comprovada por este documento.

## Objetivo
Investigar um port nativo de God of War (PS2, 2005) para Xbox 360 RGH, respeitando os direitos autorais: o repositório não deve incluir ISO, executáveis originais, assets, áudio, vídeos ou código derivado não autorizado. Usar apenas arquivos de uma cópia legítima fornecida localmente pelo usuário e confirmar licenças antes de reutilizar código de terceiros.

## Entregáveis, na ordem
1. **Xenon.elf** — primeiro artefato de teste, somente após haver um alvo executável real e uma toolchain Xbox 360/libXenon validada.
2. **default.xex** — etapa seguinte, após conversão/ligação compatível e teste no hardware ou ambiente RGH.
3. **Port jogável** — só declarar quando boot, renderização, controles, áudio, vídeos, salvamento e progressão forem testados.

## Frentes paralelas

### A — Auditoria e arquitetura
- Inventariar o repositório, licenças, dependências, formatos e lacunas.
- Definir limites claros entre código original, código de runtime e dados extraídos localmente.
- Criar matriz de compatibilidade por subsistema e por teste.

### B — CPU Emotion Engine
- Investigar caminho de recompilação/interpretação MIPS R5900 para PowerPC Xenon.
- Mapear instruções, registradores, exceções, delay slots e comportamento de ponto flutuante.
- Criar testes unitários pequenos e comparações de referência; não assumir compatibilidade sem resultados.

### C — VU0/VU1 e microprogramas
- Inventariar operações vetoriais e microprogramas usados pelo jogo.
- Prototipar tradução para PowerPC ou execução interpretada.
- Validar resultados numéricos e sincronização antes de integrar ao jogo.

### D — Gráficos GS
- Separar comandos do Graphics Synthesizer, texturas, buffers, blending, depth e efeitos.
- Criar uma camada de abstração para o pipeline gráfico do Xbox 360.
- Priorizar primeiro um teste de desenho mínimo; efeitos avançados permanecem pendentes até validação visual.

### E — IOP, áudio e mídia
- Inventariar módulos de I/O, DMA, temporizadores, SPU2/áudio, controles e reprodução de vídeos.
- Criar stubs somente para desenvolvimento; não classificá-los como implementação funcional.
- Testar cada serviço isoladamente antes de declarar suporte.

### F — Plataforma Xbox 360 / toolchain
- Verificar disponibilidade e funcionamento de compilador PowerPC Xenon, linker, bibliotecas e conversores.
- Estabelecer build reprodutível em CI quando a toolchain puder ser usada legalmente e com segurança.
- Validar primeiro ELF; depois gerar XEX e testar inicialização em console RGH.

### G — Integração, desempenho e QA
- Definir testes de boot, cenas, frame pacing, memória, controles, áudio, saves e estabilidade.
- Medir CPU, GPU, memória e tempos de quadro em hardware real; evitar estimativas sem medição.
- Manter logs de build, artefatos, commits e resultados de teste por etapa.

## Critérios de conclusão
- **Planejado:** documentado, sem código funcional comprovado.
- **Implementado:** código escrito, ainda sem confirmação de build/teste.
- **Compilado:** build terminou com sucesso e log preservado.
- **Testado:** teste executado, ambiente e resultado registrados.
- **Validado no Xbox 360 RGH:** execução real comprovada no hardware-alvo.

## Próxima etapa
Fazer inventário completo do repositório e registrar a toolchain disponível. Não marcar percentuais de implementação ou prometer um ELF/XEX até existirem código, build e evidências correspondentes.
