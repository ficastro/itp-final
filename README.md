# Gerador e Leitor de código de barras (EAN-8)

Repositório contendo um Gerador e Leitor de código de barras (EAN-8), escrito em C.

Projeto desenvolvido como atividade avaliativa da discipllina "Introdução às Técnicas de Programação" 2024.2, componente do Bacharelado em Tecnologia da Informação, UFRN.

## Estrutura

<h3>Função: Criar código de barras .pbm (create_pbm.c)</h3>

A inicialização do executável pode conter os seguintes argumentos opcionais. Se não forem especificados, o programa utilizará os valores padrões.

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
            <td>(Thickness) Grossura de cada área (barras ou espaços vazios)</td>
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
            <td>(Name) Nome do arquivo .pbm gerado</td>
            <td>"barcode"</td>
        </tr>
    </tbody>
</table>
<br>
<h3>Função: Ler código de barras .pbm (read_pbm.c)</h3>

O executável requer como input apenas o nome do arquivo .pbm já salvo na mesma pasta do programa, que lê o arquivo do código de barras e o converte para o formato decimal do EAN-8.

##
<br><br>
<small><i>Projeto criado por Fernando Iglessias de Castro Gava e Olive Oliveira Medeiros.</i></small>