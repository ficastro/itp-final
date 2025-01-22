# Gerador e Leitor de código de barras (EAN-8)

Repositório contendo um Gerador e Leitor de código de barras (EAN-8), escrito em C.

Projeto desenvolvido como atividade avaliativa da discipllina "Introdução às Técnicas de Programação" 2024.2, componente do Bacharelado em Tecnologia da Informação, UFRN.

## Estrutura

<h3>Função: Criar código de barras .pbm (create_pbm.c)</h3>

A inicialização do programa pode conter os seguintes argumentos opcionais. Se não forem especificados, o programa utilizará os valores padrões.

<table>
    <thead>
        <tr>
            <th>Argumento</th>
            <th>Tipo</th>
            <th>Significado</th>
            <th>Padrão</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>-s</td>
            <td>int</td>
            <td>(Spacing) Espaçamento inicial e final (bordas do código de barras)</td>
            <td>1</td>
        </tr>
        <tr>
            <td>-t</td>
            <td>int</td>
            <td>(Thickness) Grossura de cada área, barras ou espaços vazios</td>
            <td>1</td>
        </tr>
        <tr>
            <td>-h</td>
            <td>int</td>
            <td>(Height) Altura do código de barras</td>
            <td>10</td>
        </tr>
        <tr>
            <td>-n</td>
            <td>str</td>
            <td>(Name) Nome do arquivo .pbm gerado (deve ser inserido entre aspas)</td>
            <td>"barcode"</td>
        </tr>
    </tbody>
</table>